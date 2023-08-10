/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:28:05 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/23 11:46:53 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	while (str && str[++i])
	{
		if (ft_isdigit(str[0]))
			return (NULL);
		if (!next_char(str[i]))
			break ;
	}
	if (!i)
		return (NULL);
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		exit_dollar(data, E_MALLOC, "get_var_main");
	j = -1;
	while (++j < i)
		res[j] = str[j];
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
		exit_dollar(p, E_MALLOC, "get_before_dollar");
	while (++i < size)
		res[i] = str[i];
	res[i] = '\0';
	p->i += ft_strlen(res);
	return (res);
}

void	join_n_clean(t_token *temp, t_data *p)
{
	if (temp->token[p->i] == '?')
	{
		p->p->var_name = ft_strdup("1");
		if (!p->p->var_name)
			exit_dollar(p, E_MALLOC, "ft_strdup (var_name)");
		p->p->var_value = ft_itoa(g_ret_value);
		if (!p->p->var_value)
			exit_dollar(p, E_MALLOC, "ft_itoa ($?)");
		p->p->to_free = 1;
	}
	else
	{
		p->p->var_name = get_var_name(p, temp->token + p->i);
		if (p->p->var_name)
			p->p->var_value = ft_getenv(p->env, p->p->var_name);
		else
		{
			p->p->var_name = ft_strdup("1");
			if (!p->p->var_name)
				exit_dollar(p, E_MALLOC, "ft_strdup");
		}
	}
}

int	replace_var(t_token *temp, t_data *p)
{
	p->p->before = get_before_dollar(temp->token, p, -1, -1);
	p->i++;
	join_n_clean(temp, p);
	p->p->before_and_value = ft_strjoin_dollar(p, p->p->before, 
			p->p->var_value);
	p->p->new_token = ft_strjoin_dollar(p, p->p->before_and_value, temp->token 
			+ ft_strlen(p->p->before) + ft_strlen(p->p->var_name) + 1);
	free(temp->token);
	temp->token = ft_strdup(p->p->new_token);
	if (!temp->token)
		exit_dollar(p, E_MALLOC, "ft_strdup (temp->token in expand)");
	free_expand(p->p);
	temp->from_expand = 1;
	return (0);
}

int	expand_tokens(t_token **tokens, t_data *data)
{
	t_token	*temp;

	temp = *tokens;
	data->p->new_token = NULL;
	while (temp)
	{
		data->p->i = 0;
		if (temp->limiter == 0)
		{
			while (processed_line(temp->token, data->p))
			{
				set_to_null(data->p);
				if (replace_var(temp, data))
					return (1);
				data->i = 0;
			}
		}
		temp = temp->next;
	}
	return (0);
}
