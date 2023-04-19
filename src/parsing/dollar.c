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

int	next_char(char c)
{
	if (c == '@' || c == '#' || c == '%' || c == '^' || c == '*' || c == '-'
		|| c == '+' || c == '=' || c == '{' || c == '}' || c == '[' || c == ']'
		|| c == '\\' || c == ':' || c == ',' || c == '.' || c == '/'
		|| c == '?' || c == '~' || c == '$')
		return (0);
	else
		return (1);
}

int	find_dollar(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '$')
			return (1);
	return (0);
}

int	get_size(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (i == 0 && str[i] == '$')
			break ;
		else if (i != 0 && str[i] == '$' && str[i - 1] != '\\')
			break ;
		i++;
	}
	return (i);
}

char	*dup_till_charset(t_parsing *p, char *str)
{
	char	*res;
	int		size;
	int		i;
	int		j;

	size = get_size(str);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		res[j] = str[i];
		j++;
		i++;
	}
	res[j] = '\0';
	p->i += i;
	return (res);
}

char	*cut_var_name(t_parsing *p, char *var)
{
	char	*name;
	int		i;

	if (var && ft_isdigit(var[0]))
		return (NULL);
	i = 0;
	while (var && var[i] && next_char(var[i]))
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (var && var[i] && next_char(var[i]))
	{
		name[i] = var[i];
		i++;
	}
	name[i] = '\0';
	p->i += i;
	return (name);
}

char	*dup_till_word(t_parsing *p, char *var)
{
	char	*res;
	char	*name;
	char	*value;

	if (var[0] == '$')
	{
		p->i++;
		var++;
	}
	name = cut_var_name(p, var);
	p->var_name_len = ft_strlen(name) + 1;
	value = ft_getenv(p->env, name);
	res = ft_strdup(value);
	free(name);
	free(value);
	if (!res)
		return (NULL);
	return (res);
}

int	get_index_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str)
	}
}

void	replace_var(t_token *temp, t_parsing *p)
{
	char	*dup_before;
	char	*dup_var;
	char	*expand;
	char	*new_str;
	int		skip;

	p->i = 0;
	while (find_dollar(temp->token))
	{
		dup_before = dup_till_charset(p, temp->token);
		dup_var = dup_till_word(p, temp->token + p->i);
		expand = ft_strjoin(dup_before, dup_var);
		printf("expand=%s\n", expand);
		skip = get_index_dollar(temp->token);
		printf("%d\n", skip);
		new_str = ft_strjoin(expand, temp->token + skip);
		free(temp->token);
		temp->token = ft_strjoin(expand, new_str);
		printf("token+p->i=%s\n", temp->token + p->i);
		free(dup_before);
		free(dup_var);
		free(new_str);
		free(expand);
		if (temp->token[p->i] == '\0')
			break ;
		//expand = ft_strjoin(dup_before, ft_getenv(p->env, dup_var));
		//printf("before :%s & var :%s, expand %s\n", dup_before, dup_var, expand);
		//skip = ft_strlen(dup_before) + ft_strlen(ft_getenv(p->env, dup_var));
		// free(temp->token);
		// temp->token = ft_strjoin(expand, temp->token + skip);
		// free(dup_before);
		// free(dup_var);
		// free(expand);
	}
}

void	navigate_tokens(t_token **tokens, t_parsing *p)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		if (find_dollar(temp->token))
			replace_var(temp, p);
		temp = temp->next;
	}
}
