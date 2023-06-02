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
		if (ft_isdigit(str[i]))
			break ;
		if (!next_char(str[i]))
			break ;
	}
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

char	*get_before_dollar(char *str, t_data *p)
{
	int		i;
	int		size;
	char	*res;

	size = 0;
	while (str && str[size])
	{
		p_quote(p->p, str[size]);
		if (str[size - 1] != '$' && str[size] == '$' && str[size + 1] != '$' && !p->p->quote)
			break ;
		else if (str[size - 2] == '$' && str[size - 1] == '$' && str[size] == '$' && str[size + 1] != '$' && !p->p->quote)
			break ;
		size++;
	}
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	p->i += ft_strlen(res);
	return (res);
}

void	free_expand(t_parsing *p)
{
	if (p->var_name)
		free(p->var_name);
	if (p->before)
		free(p->before);
	if (p->before_and_value)
		free(p->before_and_value);
	if (p->new_token)
		free(p->new_token);
}

void	replace_var(t_token *temp, t_data *p)
{
	p->p->before = get_before_dollar(temp->token, p);
	p->i++;
	p->p->var_name = get_var_name(temp->token + p->i);
	p->p->var_value = ft_getenv(p->env, p->p->var_name);
	p->p->before_and_value = ft_strjoin_dollar(p->p->before, p->p->var_value);
	p->p->new_token = ft_strjoin_dollar(p->p->before_and_value, temp->token \
	+ ft_strlen(p->p->before) + ft_strlen(p->p->var_name) + 1);
	free(temp->token);
	temp->token = ft_strdup(p->p->new_token);
	printf("before:%s\nvar_value:%s\nbefore_and_value:%s\nvar_name:%s\nnew_token:%s\n", \
	p->p->before, p->p->var_value, p->p->before_and_value, p->p->var_name, p->p->new_token);
	free_expand(p->p);
}

void	expand_tokens(t_token **tokens, t_data *data)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		data->p->i = 0;
		while (processed_line(temp->token, data->p))
		{
			replace_var(temp, data);
			data->i = 0;
		}
		temp = temp->next;
	}
}
