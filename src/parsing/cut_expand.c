/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:27:47 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/16 16:27:49 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_in_middle(t_token	*prev, t_token *next, char **a, t_data *d)
{
	int		i;
	t_token	*temp;

	temp = NULL;
	i = -1;
	while (a[++i])
		ft_tokenadd_back(&temp, ft_tokennew(a[i]));
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

int	copy_propre_quote(t_token *temp)
{
	char	*new;
	int		i_old;
	int		i_new;

	new = malloc(sizeof(char) * (ft_strlen(temp->token) - 1));
	if (!new)
		return (1);
	i_old = -1;
	i_new = -1;
	while (temp->token[++i_old])
	{
		if (i_old == 0)
			i_old++;
		else if (i_old == (int)ft_strlen(temp->token))
			break ;
		new[++i_new] = temp->token[i_old];
	}
	new[i_new] = '\0';
	free(temp->token);
	temp->token = new;
	return (0);
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
		else if (temp->from_expand)
		{
			if (remove_quotes_expand(&data->tokens, data))
				return (1);
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
