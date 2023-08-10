/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:27:47 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/23 11:26:37 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	link_list(t_data *d, t_token *prev, t_token *next, t_token *temp)
{
	if (prev)
	{
		temp->prev = prev;
		prev->next = temp;
	}
	else
		d->tokens = temp;
	while (temp->next)
	{
		temp->from_expand = 1;
		temp = temp->next;
	}
	temp->from_expand = 1;
	if (next)
	{
		temp->next = next;
		next->prev = temp;
	}
}

void	add_token_in_middle(t_token	*prev, t_token *next, char **a, t_data *d)
{
	int		i;
	t_token	*temp;
	t_token	*save;

	temp = NULL;
	i = -1;
	while (a[++i])
	{
		ft_tokenadd_back(&temp, ft_tokennew(ft_strdup(a[i])));
		save = temp;
		while (save)
		{
			if (!save || !save->token)
			{
				free_token(temp);
				free_array(a);
				exit_parsing(d, E_MALLOC, "add_token_in_middle");
			}
			save = save->next;
		}
	}
	link_list(d, prev, next, temp);
}

int	cutting_expand(t_data *data)
{
	char	**array;
	t_token	*temp;
	t_token	*save;

	temp = data->tokens;
	while (temp)
	{
		save = temp->next;
		if (temp->token && !temp->token[0])
			;
		else if (temp->from_expand && !temp->in_quote)
		{
			array = ft_split(temp->token, ' ');
			if (!array)
				return (1);
			add_token_in_middle(temp->prev, temp->next, array, data);
			free_array(array);
			free(temp->token);
			free(temp);
		}
		temp = save;
	}
	return (0);
}
