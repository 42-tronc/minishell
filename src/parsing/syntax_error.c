/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:54:49 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/29 11:22:25 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	similar_type(t_token *temp)
{
	int	symbol1;
	int	symbol2;

	symbol1 = 0;
	symbol2 = 0;
	if (!ft_strcmp(temp->type, PIPE) && !ft_strcmp(temp->prev->type, PIPE))
		g_ret_value = 2;
	if (!ft_strcmp(temp->type, PIPE) && !ft_strcmp(temp->prev->type, PIPE))
		return (1);
	if (!ft_strcmp(temp->type, CHEVRON_L) \
	|| !ft_strcmp(temp->type, CHEVRON_R) \
	|| !ft_strcmp(temp->type, CHEVRON_RR) \
	|| !ft_strcmp(temp->type, HERE_DOC) \
	|| !ft_strcmp(temp->type, PIPE))
		symbol1 = 1;
	if (!ft_strcmp(temp->prev->type, CHEVRON_L) \
	|| !ft_strcmp(temp->prev->type, CHEVRON_R) \
	|| !ft_strcmp(temp->prev->type, CHEVRON_RR) \
	|| !ft_strcmp(temp->prev->type, HERE_DOC))
		symbol2 = 1;
	if (symbol1 && symbol2)
		g_ret_value = 2;
	if (symbol1 && symbol2)
		return (1);
	return (0);
}

int	check_last_token(t_token *temp)
{
	while (temp->next)
		temp = temp->next;
	if (!ft_strcmp(temp->type, CHEVRON_L) \
	|| !ft_strcmp(temp->type, CHEVRON_R) \
	|| !ft_strcmp(temp->type, CHEVRON_RR) \
	|| !ft_strcmp(temp->type, HERE_DOC) \
	|| !ft_strcmp(temp->type, PIPE))
	{
		g_ret_value = 2;
		ft_putendl_fd(" syntax error near unexpected token `newline'", 2);
		return (1);
	}
	return (0);
}

int	syntax_error(t_data *data)
{
	t_token	*t;

	t = data->tokens;
	while (t)
	{
		if (!t->prev && !ft_strcmp(t->type, PIPE))
		{
			ft_putendl_fd(" syntax error near unexpected token", 2);
			g_ret_value = 2;
			return (1);
		}
		else if (t->prev)
		{
			if (similar_type(t))
			{
				ft_putendl_fd(" syntax error near unexpected token", 2);
				g_ret_value = 2;
				return (1);
			}
		}
		t = t->next;
	}
	if (check_last_token(data->tokens))
		return (1);
	return (0);
}
