/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <aascedu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:16:55 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/06 10:09:55 by aascedu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (lst == NULL)
	{
		return ;
	}
	temp = *lst;
	if (!temp)
	{
		*lst = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

// Missing error managment and leaks are occuring in case of error.
t_token	*ft_tokennew(void *content)
{
	t_token	*dst;

	dst = malloc(sizeof(t_token));
	if (!dst)
		return (NULL);
	if (dst)
	{
		dst->token = (char *)content;
		dst->token_id = NULL;
		dst->next = NULL;
	}
	return (dst);
}

void	free_token(t_token *tokens)
{
	t_token *current;
	t_token *temp1;

	current = tokens;
	while (current != NULL)
	{
		temp1 = current;
		current = current->next;
		free(temp1->token);
		free(temp1);
	}
}