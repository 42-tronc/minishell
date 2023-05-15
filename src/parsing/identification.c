/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:51:50 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/15 15:33:43 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_separator(t_token *temp)
{
	if (temp->token[0] == '|')
		temp->type = PIPE;
	else if (temp->token[0] == '>' && temp->token[1] == '>')
		temp->type = HERE_DOC_END;
	else if (temp->token[0] == '<' && temp->token[1] == '<')
		temp->type = HERE_DOC;
	else if (temp->token [0] == '<' && temp->token[1] == '\0')
		temp->type = CHEVRON_L;
	else if (temp->token[0] == '>' && temp->token[1] == '\0')
		temp->type = CHEVRON_R;
	else
		temp->type = CMD;
}

void	which_id_to_give(t_token *temp)
{
	temp->pipe_block = temp->prev->pipe_block;
	if (!ft_strcmp(temp->prev->type, CHEVRON_L))
		temp->type = INFILE;
	else if (!ft_strcmp(temp->prev->type, CHEVRON_R))
		temp->type = OUTFILE;
	else if (!ft_strcmp(temp->prev->type, INFILE))
		temp->type = CMD;
	else if (!ft_strcmp(temp->prev->type, CMD))
		temp->type = ARG;
	else if (!ft_strcmp(temp->prev->type, ARG))
		temp->type = ARG;
	else if (!ft_strcmp(temp->prev->type, HERE_DOC))
		temp->type = LIMITER;
	else if (!ft_strcmp(temp->prev->type, HERE_DOC_END))
		temp->type = OUTFILE;
	else if (!ft_strcmp(temp->prev->type, LIMITER))
		temp->type = CMD;
	else if (!ft_strcmp(temp->prev->type, PIPE))
		get_separator(temp);
}

void	command_arg_file(t_token *temp)
{
	while (temp)
	{
		if (temp->token[0] == '|')
			get_separator(temp);
		else
			which_id_to_give(temp);
		temp = temp->next;
	}
}

void	id_tokens(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	if (temp->prev == NULL)
	{
		first_token(temp);
		temp = temp->next;
	}
	command_arg_file(temp);
}
