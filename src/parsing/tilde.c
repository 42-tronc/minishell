/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:57:43 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/31 10:57:44 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tilde(t_parsing *p, char *str)
{
	if (str)
	{
		p_quote(p, str[0]);
		if (str[0] == '~' && !p->quote)
			return (1);
	}
	return (0);
}

int	replace_tilde(t_token *temp, t_data *data)
{
	char	*copy;

	(void)data;
	copy = ft_strdup(temp->token);
	if (!copy)
		return (1);
	free(temp->token);
	if (copy && (copy[1] == '/' || !copy[1]))
	{
		temp->token = ft_strjoin(ft_getenv(data->env, "HOME"), copy + 1);
		if (!temp->token)
			return (free(copy), 1);
	}
	else
	{
		temp->token = ft_strdup(copy);
		if (!temp->token)
			return (free(copy), 1);
	}
	free(copy);
	return (0);
}

int	expand_tilde(t_token **tokens, t_data *data)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		if (is_tilde(data->p, temp->token))
			if (replace_tilde(temp, data))
				return (1);
		temp = temp->next;
	}
	return (0);
}
