/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:05:57 by croy              #+#    #+#             */
/*   Updated: 2023/07/25 16:47:38 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_cpy(char *dst, char *src, int index)
{
	size_t	i;

	i = 0;
	while (src && src[i])
	{
		dst[index] = src[i];
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
char	*ft_strjoin_heredoc(char *s1, char *s2)
{
	size_t	index;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!dst)
		return (NULL);
	index = str_cpy(dst, s1, 0);
	index = str_cpy(dst, s2, index);
	index = str_cpy(dst, "\n", index);
	dst[index] = '\0';
	free(s1);
	free(s2);
	return (dst);
}
