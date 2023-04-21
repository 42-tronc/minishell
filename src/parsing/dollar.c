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
		|| c == '?' || c == '~' || c == '$' || c == '\'' || c == '\"' || c == ' ')
		return (0);
	else
		return (1);
}

int	processed_line(char *str)
{
	int	i;
	int	keep;

	i = -1;
	keep = 0;
	while (str && str[++i])
	{
		if (i == 0 && str[i] == '$')
			keep = 1;
		if (i > 0 && str[i - 1] == '$' && (next_char(str[i]) || ft_isdigit(str[i])))
			keep = 1;
	}
	return (keep);
}

char	*get_var_name(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (str && str[i])
	{
		if (!next_char(str[i]))
			break ;
		i++;
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

static int	str_cpy_dollar(char *dst, char *src, int index)
{
	size_t	i;

	i = 0;
	while (src && src[i])
	{
		dst[index] = ((char *)src)[i];
		i++;
		index++;
	}
	return (index);
}

/**
 * @brief allocates and return a new string being s1 + s2
 *
 * @param s1 first string
 * @param s2 second string to add to s1
 * @return char* concatenated string of s1+s2 NULL if allocation fails
 */
char	*ft_strjoin_dollar(char const *s1, char const *s2)
{
	size_t	index;
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	index = str_cpy_dollar(dst, (char *)s1, 0);
	index = str_cpy_dollar(dst, (char *)s2, index);
	dst[index] = '\0';
	return (dst);
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
		new_token = ft_strjoin_dollar(before_and_value, temp->token + ft_strlen(before) + ft_strlen(var_name) + 1);
		free(temp->token);
		temp->token = ft_strdup(new_token);
		// printf("before:%s\n", before);
		// printf("p->i=%d\n", p->i);
		// printf("str+p->i:%s\n", temp->token + p->i);
		// printf("var_name:%s\n", var_name);
		// printf("var_value:%s\n", var_value);
		// printf("new_token:%s\n", new_token);
		// printf("bav:%s\n", before_and_value);
		// printf("b:%p, vv:%p, bav:%p, nt:%p, vn:%p, tt:%p\n", before, var_value, before_and_value, new_token, var_name, temp->token);
		// free(var_value);
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
