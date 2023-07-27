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
	int		k;
	t_token	*temp;

	temp = NULL;
	i = -1;
	k = -1;
	while (a[++i])
	{
		ft_tokenadd_back(&temp, ft_tokennew(a[i]));
		while (++k <= i)
		{
			if (!temp->token)
			{
				free_token(temp);
				free_token(d->tokens);
				free(d->p);
				free_list(d->env);
				free(d);
				exit (1);
			}
		}
	}
	link_list(d, prev, next, temp);
}

void	free_cutting_expand(char **array, t_token *temp)
{
	free(array);
	free(temp->token);
	free(temp);
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
			free_cutting_expand(array, temp);
		}
		temp = save;
	}
	return (0);
}
