/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:57:43 by aascedu           #+#    #+#             */
/*   Updated: 2023/08/11 13:02:28 by croy             ###   ########lyon.fr   */
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

void	exit_tilde(t_data *data, int code, char *source, char *copy)
{
	free(copy);
	free_token(data->tokens);
	free_list(data->env);
	free(data->p);
	free(data);
	print_error(code, source);
	rl_clear_history();
	exit (1);
}

int	replace_tilde(t_token *temp, t_data *data)
{
	char	*copy;

	(void)data;
	copy = ft_strdup(temp->token);
	if (!copy)
		exit_tilde(data, E_MALLOC, "replace_tilde", copy);
	free(temp->token);
	if (copy && (copy[1] == '/' || !copy[1]))
	{
		temp->token = ft_strjoin(ft_getenv(data->env, "HOME"), copy + 1);
		if (!temp->token)
			exit_tilde(data, E_MALLOC, "replace_tilde", copy);
	}
	else
	{
		temp->token = ft_strdup(copy);
		if (!temp->token)
			exit_tilde(data, E_MALLOC, "replace_tilde", copy);
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
