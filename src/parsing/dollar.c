/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:28:05 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/17 10:28:07 by aascedu          ###   ########.fr       */
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

char	*get_before_dollar(char *str, t_parsing *p)
{
	int		i;
	int		size;
	char	*res;

	size = 0;
	while (str && str[size])
	{
		if (str[size] == '$')
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

void	replace_var(t_token *temp, t_parsing *p)
{
	char	*before;
	char	*var_value;
	char	*before_and_value;
	char	*new_token;
	char	*var_name;

	before = get_before_dollar(temp->token, p);
	p->i++;
	var_name = get_var_name(temp->token + p->i);
	var_value = getenv(var_name);
	before_and_value = ft_strjoin_dollar(before, var_value);
	new_token = ft_strjoin_dollar(before_and_value, temp->token \
	+ ft_strlen(before) + ft_strlen(var_name) + 1);
	free(temp->token);
	temp->token = ft_strdup(new_token);
	free(var_name);
	free(before_and_value);
	free(before);
	free(new_token);
}

void	navigate_tokens(t_token **tokens, t_parsing *p)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		while (processed_line(temp->token))
		{
			p->i = 0;
			replace_var(temp, p);
		}
		temp = temp->next;
	}
}
