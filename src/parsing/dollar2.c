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

int	next_char(char c)
{
	if (c == '@' || c == '#' || c == '%' || c == '^' || c == '*' || c == '-'
		|| c == '+' || c == '=' || c == '{' || c == '}' || c == '[' || c == ']'
		|| c == '\\' || c == ':' || c == ',' || c == '.' || c == '/'
		|| c == '?' || c == '~' || c == '$' || c == '\'' || c == '\"'
		|| c == ' ')
		return (0);
	else
		return (1);
}

int	processed_line(char *str, t_parsing *p)
{
	int	i;
	int	found_dollar;
	int	found_alpha;

	i = 0;
	found_dollar = 0;
	found_alpha = 0;
	while (str && str[i])
	{
		p_quote(p, str[i]);
		if (!p->quote && str[i] == '$')
			found_dollar = 1;
		else if (found_dollar && ft_isalpha(str[i]))
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
