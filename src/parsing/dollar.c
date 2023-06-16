/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:28:05 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/27 10:49:28 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	while (str && str[++i])
	{
		if (ft_isdigit(str[i]))
			i++;
		if (ft_isdigit(str[i]) || !next_char(str[i]))
			break ;
	}
	if (!i)
		return (NULL);
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (j < i)
	{
		res[j] = str[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*get_before_dollar(char *str, t_data *p, int i, int size)
{
	char	*res;

	while (str && str[++size])
	{
		p_quote(p->p, str[size]);
		if (size == 0 && str[size] == '$' && str[size + 1] != '$')
			break ;
		if (size >= 1 && str[size - 1] != '$' && str[size] == '$' \
		&& str[size + 1] != '$' && !p->p->quote)
			break ;
		else if (size >= 2 && str[size - 2] == '$' && str[size - 1] == '$' \
		&& str[size] == '$' && str[size + 1] != '$' && !p->p->quote)
			break ;
	}
	if (!size)
		return (NULL);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	while (++i < size)
		res[i] = str[i];
	res[i] = '\0';
	p->i += ft_strlen(res);
	return (res);
}

void	free_expand(t_parsing *p)
{
	if (p->var_value && p->var_name[0] == '1')
		free(p->var_value);
	if (p->var_name)
		free(p->var_name);
	if (p->before)
		free(p->before);
	if (p->before_and_value)
		free(p->before_and_value);
	if (p->new_token)
		free(p->new_token);
}

int	replace_var(t_token *temp, t_data *p)
{
	p->p->before = get_before_dollar(temp->token, p, -1, -1);
	p->i++;
	if (temp->token[p->i] == '?')
	{
		p->p->var_name = ft_strdup("1");
		p->p->var_value = ft_strdup("[retValue]");
	}
	else
	{
		p->p->var_name = get_var_name(temp->token + p->i);
		if (p->p->var_name)
			p->p->var_value = ft_getenv(p->env, p->p->var_name);
	}
	p->p->before_and_value = ft_strjoin_dollar(p->p->before, p->p->var_value);
	p->p->new_token = ft_strjoin_dollar(p->p->before_and_value, temp->token \
	+ ft_strlen(p->p->before) + ft_strlen(p->p->var_name) + 1);
	if (!p->p->new_token)
		return (1);
	free(temp->token);
	temp->token = ft_strdup(p->p->new_token);
	free_expand(p->p);
	return (0);
}

int	expand_tokens(t_token **tokens, t_data *data)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		data->p->i = 0;
		while (processed_line(temp->token, data->p))
		{
			if (replace_var(temp, data))
				return (1);
			data->i = 0;
			temp->from_expand = 1;
		}
		temp = temp->next;
	}
	return (0);
}
