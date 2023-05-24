/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:16:55 by arthurasced       #+#    #+#             */
/*   Updated: 2023/05/24 10:54:00 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (lst == NULL)
		return ;
	temp = *lst;
	if (!temp)
	{
		new->prev = NULL;
		*lst = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

t_token	*ft_tokennew(void *content)
{
	t_token	*dst;

	dst = malloc(sizeof(t_token));
	if (!dst)
		return (NULL);
	dst->token = (char *)content;
	dst->type = NULL;
	dst->next = NULL;
	dst->pipe_block = 0;
	return (dst);
}

void	free_token(t_token *tokens)
{
	t_token	*current;
	t_token	*temp1;

	current = tokens;
	while (current != NULL)
	{
		temp1 = current;
		current = current->next;
		free(temp1->token);
		free(temp1);
	}
}
