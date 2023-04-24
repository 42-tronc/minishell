/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:51:50 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/24 08:51:51 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_separator(t_token *temp)
{
	if (temp->token[0] == '|')
		temp->token_id = PIPE;
	if (temp->token [0] == '<')
		temp->token_id = CHEVRON_L;
	if (temp->token[0] == '>')
		temp->token_id = CHEVRON_R;
	return (1);
}

void	after_pipe_token(t_token *temp)
{
	if (temp->token[0] == '<')
		temp->token_id = CHEVRON_L;
	else
		temp->token_id = CMD;
}

void	which_id_to_give(t_token *temp)
{
	if (!ft_strcmp(temp->prev->token_id, CHEVRON_L))
		temp->token_id = INFILE;
	if (!ft_strcmp(temp->prev->token_id, CHEVRON_R))
		temp->token_id = OUTFILE;
	else if (!ft_strcmp(temp->prev->token_id, INFILE))
		temp->token_id = CMD;
	else if (!ft_strcmp(temp->prev->token_id, CMD))
		temp->token_id = ARG;
	else if (!ft_strcmp(temp->prev->token_id, ARG))
		temp->token_id = ARG;
	else if (!ft_strcmp(temp->prev->token_id, PIPE))
		after_pipe_token(temp);
}

int	command_arg_file(t_token *temp)
{
	int	stop;

	stop = 0;
	while (temp)
	{
		which_id_to_give(temp);
		stop++;
		if (temp->next && is_separator(temp->next))
			break ;
		temp = temp->next;
	}
	return (stop);
}

void	id_tokens(t_token **tokens)
{
	t_token	*temp;
	int		stop;
	int		i;

	temp = *tokens;
	while (temp != NULL)
	{
		i = 0;
		if (temp->prev == NULL)
			stop = first_token(temp);
		else if (!is_separator(temp))
			stop = command_arg_file(temp);
		else
			stop = get_separator(temp);
		while (i++ < stop)
			temp = temp->next;
	}
}
