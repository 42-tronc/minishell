/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:51:50 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/03 14:21:40 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_separator(t_token *temp)
{
	if (temp->token[0] == '|')
		temp->token_id = PIPE;
	else if (temp->token[0] == '>' && temp->token[1] == '>')
		temp->token_id = HERE_DOC_END;
	else if (temp->token[0] == '<' && temp->token[1] == '<')
		temp->token_id = HERE_DOC;
	else if (temp->token [0] == '<' && temp->token[1] == '\0')
		temp->token_id = CHEVRON_L;
	else if (temp->token[0] == '>' && temp->token[1] == '\0')
		temp->token_id = CHEVRON_R;
	else
		temp->token_id = CMD;
}

void	which_id_to_give(t_token *temp)
{
	temp->pipe_block = temp->prev->pipe_block;
	if (!ft_strcmp(temp->prev->token_id, CHEVRON_L))
		temp->token_id = INFILE;
	else if (!ft_strcmp(temp->prev->token_id, CHEVRON_R))
		temp->token_id = OUTFILE;
	else if (!ft_strcmp(temp->prev->token_id, INFILE))
		temp->token_id = CMD;
	else if (!ft_strcmp(temp->prev->token_id, CMD))
		temp->token_id = ARG;
	else if (!ft_strcmp(temp->prev->token_id, ARG))
		temp->token_id = ARG;
	else if (!ft_strcmp(temp->prev->token_id, HERE_DOC))
		temp->token_id = LIMITER;
	else if (!ft_strcmp(temp->prev->token_id, HERE_DOC_END))
		temp->token_id = OUTFILE;
	else if (!ft_strcmp(temp->prev->token_id, LIMITER))
		temp->token_id = CMD;
	else if (!ft_strcmp(temp->prev->token_id, PIPE))
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
