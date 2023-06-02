/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:51:50 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/24 10:54:00 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(t_token *temp)
{
	if (temp->token[0] == '|' || temp->token[0] == '<' \
	|| temp->token[0] == '>')
		return (1);
	return (0);
}

int	first_token(t_token *temp)
{
	if (temp->token[0] == '<' && temp->token[1] == '\0')
		temp->type = CHEVRON_L;
	else if (temp->token[0] == '<' && temp->token[1] == '<')
		temp->type = HERE_DOC;
	else if (temp->token[0] == '>' && temp->token[1] == '\0')
		temp->type = OUTFILE;
	else if (temp->token[0] == '>' && temp->token[1] == '>')
		temp->type = ADD;
	else if (temp->token[0] == '|')
		temp->type = MY_NULL;
	else
		temp->type = CMD;
	return (1);
}

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
		if (!ft_strcmp(temp->type, CMD))
			return (0);
		temp = temp->prev;
	}
	return (1);
}

void	choose_token_id(t_token *temp)
{
	if (!temp->prev)
		temp->type = CMD;
	else if (!ft_strcmp(temp->prev->type, MY_NULL))
		return ;
	else if (!ft_strcmp(temp->prev->type, CHEVRON_L))
		temp->type = INFILE;
	else if (!ft_strcmp(temp->prev->type, CHEVRON_R))
		temp->type = OUTFILE;
	else if (!ft_strcmp(temp->prev->type, HERE_DOC))
		temp->type = LIMITER;
	else if (!ft_strcmp(temp->prev->type, APPEND))
		temp->type = ADD;
	else if (is_first_cmd(temp))
		temp->type = CMD;
	else
		temp->type = ARG;
}

void	id_tokens(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	temp->pipe_block = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->token, "<"))
			temp->type = CHEVRON_L;
		else if (!ft_strcmp(temp->token, "<<"))
			temp->type = HERE_DOC;
		else if (!ft_strcmp(temp->token, ">"))
			temp->type = CHEVRON_R;
		else if (!ft_strcmp(temp->token, ">>"))
			temp->type = APPEND;
		else if (!ft_strcmp(temp->token, "|"))
		{
			temp->type = PIPE;
			if (temp->prev)
				temp->pipe_block = temp->prev->pipe_block + 1;
		}
		else
			choose_token_id(temp);
		if (ft_strcmp(temp->type, PIPE) && temp->prev)
			temp->pipe_block = temp->prev->pipe_block;
		temp = temp->next;
	}
}
