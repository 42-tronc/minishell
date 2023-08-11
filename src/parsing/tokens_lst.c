/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:16:55 by arthurasced       #+#    #+#             */
/*   Updated: 2023/06/23 10:31:02 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**find_head_ref(t_token *temp)
{
	while (temp->prev)
		temp = temp->prev;
	return (temp->head_ref);
}

void	delete_token(t_token **head_ref, t_token *del)
{
	if (*head_ref == NULL || del == NULL)
		return ;
	if (*head_ref == del)
		*head_ref = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del->token);
	free(del);
}

int	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (lst == NULL || new == NULL)
		return (1);
	temp = *lst;
	if (!temp)
	{
		new->prev = NULL;
		*lst = new;
		new->head_ref = lst;
		return (0);
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (0);
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
	dst->prev = NULL;
	dst->in_quote = 0;
	dst->limiter = 0;
	dst->from_expand = 0;
	dst->pipe_block = 0;
	return (dst);
}

void	free_token(t_token *tokens)
{
	t_token	*current;
	t_token	*temp1;

	if (tokens == NULL)
		return ;
	current = tokens;
	while (current != NULL)
	{
		temp1 = current;
		current = current->next;
		if (temp1->token)
			free(temp1->token);
		free(temp1);
	}
}
