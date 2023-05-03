/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:51:50 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/27 10:49:28 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_separator(t_token *temp, t_parsing *p)
{
	(void)p;
	if (temp->token[0] == '|')
	{
		temp->token_id = PIPE;
		temp->pipe_block = temp->prev->pipe_block + 1;
		return (1);
	}
	else if (temp->token[0] == '>' && temp->token[1] == '>')
		temp->token_id = APPEND;
	else if (temp->token[0] == '<' && temp->token[1] == '<')
		temp->token_id = HERE_DOC;
	else if (temp->token [0] == '<' && temp->token[1] == '\0')
		temp->token_id = CHEVRON_L;
	else if (temp->token[0] == '>' && temp->token[1] == '\0')
		temp->token_id = CHEVRON_R;
	temp->pipe_block = temp->prev->pipe_block;
	return (1);
}

void	which_id_to_give(t_token *temp, t_parsing *p)
{
	if (!temp->token_id)
		return ;
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
	else if (!ft_strcmp(temp->prev->token_id, HERE_DOC))
		temp->token_id = LIMITER;
	else if (!ft_strcmp(temp->prev->token_id, APPEND))
		temp->token_id = OUTFILE;
	else if (!ft_strcmp(temp->prev->token_id, LIMITER))
		temp->token_id = CMD;
	else if (!ft_strcmp(temp->prev->token_id, PIPE))
		get_separator(temp, p);
	if (ft_strcmp(temp->token_id, PIPE))
		temp->pipe_block = temp->prev->pipe_block;
}

int	command_arg_file(t_token *temp, t_parsing *p)
{
	int	stop;

	stop = 0;
	while (temp)
	{
		which_id_to_give(temp, p);
		stop++;
		if (temp->next && is_separator(temp->next))
			break ;
		temp = temp->next;
	}
	return (stop);
}

void	id_tokens(t_token **tokens, t_parsing *p)
{
	t_token	*temp;
	int		stop;
	int		i;

	temp = *tokens;
	temp->pipe_block = 0;
	while (temp != NULL)
	{
		i = 0;
		if (temp->prev == NULL)
			stop = first_token(temp);
		else if (!is_separator(temp))
			stop = command_arg_file(temp, p);
		else
			stop = get_separator(temp, p);
		while (i++ < stop)
			temp = temp->next;
	}
}
