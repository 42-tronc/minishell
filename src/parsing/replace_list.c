/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:06:41 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/23 11:32:50 by aascedu          ###   ########.fr       */
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

int	ft_tokensize(t_token *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

int	replace_list(t_data *data, t_token *save, int lst_size)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->token && !temp->token[0] && !temp->in_quote)
		{
			if (temp->prev)
				temp->prev->next = temp->next;
			else
				data->tokens = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			save = temp->next;
			free(temp->token);
			free(temp);
			temp = save;
			lst_size--;
		}
		else
			temp = temp->next;
	}
	if (lst_size == 0)
		return (1);
	return (0);
}
