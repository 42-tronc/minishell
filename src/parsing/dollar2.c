/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:33:34 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/27 10:49:28 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_expand(t_parsing *p)
{
	if (p->to_free != 0)
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

int	next_char(char c)
{
	if (c == '@' || c == '#' || c == '%' || c == '^' || c == '*' || c == '-'
		|| c == '+' || c == '=' || c == '{' || c == '}' || c == '[' || c == ']'
		|| c == '\\' || c == ':' || c == ',' || c == '.' || c == '/'
		|| c == '?' || c == '~' || c == '$' || c == '\'' || c == '\"'
		|| c == ' ' || c == '|' || c == '!')
		return (0);
	else
		return (1);
}

int	processed_line(char *s, t_parsing *p)
{
	int	i;
	int	found_dollar;
	int	found_alpha;

	i = 0;
	found_dollar = 0;
	found_alpha = 0;
	p->quote = 0;
	p->dquote = 0;
	while (s && s[i])
	{
		p_quote(p, s[i]);
		if (!p->quote && s[i] == '$')
			found_dollar++;
		else if (found_dollar % 2 != 0 && (ft_isalnum(s[i]) || s[i] == '?'
				|| (s[i] == '\"' && p->dquote) || (s[i] == '\'' && p->quote)))
			found_alpha = 1;
		else
			found_dollar = 0;
		i++;
	}
	return (found_alpha);
}

int	str_cpy_dollar(char *dst, char *src, int index)
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
char	*ft_strjoin_dollar(t_data *data, char const *s1, char const *s2)
{
	size_t	index;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		exit_dollar(data, E_MALLOC, "ft_strjoin_dollar");
	index = str_cpy_dollar(dst, (char *)s1, 0);
	index = str_cpy_dollar(dst, (char *)s2, index);
	dst[index] = '\0';
	return (dst);
}
