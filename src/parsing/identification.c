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

int	is_first_cmd(t_token *head)
{
	int		pipe_block;
	t_token	*temp;

	if (head->prev != NULL)
		temp = head->prev;
	else
		return (1);
	pipe_block = temp->pipe_block;
	while (temp && pipe_block == temp->pipe_block)
	{
		if (!ft_strcmp(temp->token_id, CMD))
			return (0);
		temp = temp->prev;
	}
	return (1);
}

void	choose_token_id(t_token *temp)
{
	if (!temp->prev)
		temp->token_id = CMD;
	else if (!ft_strcmp(temp->prev->token_id, CHEVRON_L))
		temp->token_id = INFILE;
	else if (!ft_strcmp(temp->prev->token_id, CHEVRON_R))
		temp->token_id = OUTFILE;
	else if (!ft_strcmp(temp->prev->token_id, HERE_DOC))
		temp->token_id = LIMITER;
	else if (!ft_strcmp(temp->prev->token_id, APPEND))
		temp->token_id = FILE_APPEND;
	else if (is_first_cmd(temp))
		temp->token_id = CMD;
	else
		temp->token_id = ARG;
}

void	id_tokens(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	temp->pipe_block = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->token, "<"))
			temp->token_id = CHEVRON_L;
		else if (!ft_strcmp(temp->token, "<<"))
			temp->token_id = HERE_DOC;
		else if (!ft_strcmp(temp->token, ">"))
			temp->token_id = CHEVRON_R;
		else if (!ft_strcmp(temp->token, ">>"))
			temp->token_id = APPEND;
		else if (!ft_strcmp(temp->token, "|"))
		{
			temp->token_id = PIPE;
			temp->pipe_block = temp->prev->pipe_block + 1;
		}
		else
			choose_token_id(temp);
		if (ft_strcmp(temp->token_id, PIPE) && temp->prev)
			temp->pipe_block = temp->prev->pipe_block;
		temp = temp->next;
	}
}
