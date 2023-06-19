/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:06:41 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/16 10:49:01 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	need_to_new(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->token && tokens->token[0] == '\0')
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

int	replace_list(t_data *data)
{
	t_token	*temp;
	t_token	*save;

	if (need_to_new(data->tokens))
		return (0);
	temp = data->tokens;
	while (temp)
	{
		if (temp->token && !temp->token[0] && !temp->in_quote)
		{
			if (&temp == find_head_ref(temp))
				data->tokens = temp->next;
			if (temp->prev)
				temp->prev->next = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			save = temp->next;
			free(temp->token);
			free(temp);
			temp = save;
		}
		else
			temp = temp->next;
	}
	return (0);
}
