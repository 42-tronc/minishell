/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:18:44 by croy              #+#    #+#             */
/*   Updated: 2023/08/02 11:39:37 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_lines(char const *str, char c)
{
	size_t	i;
	size_t	lines;

	i = 0;
	lines = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			lines++;
		i++;
	}
	return (lines);
}

static char	*write_word(char *s1, char c)
{
	size_t	i;
	size_t	len;
	char	*dst;

	i = 0;
	len = 0;
	while (s1[len] && s1[len] != c)
		len++;
	dst = malloc(sizeof(char) * (len + 2));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i++] = '/';
	dst[i] = '\0';
	return (dst);
}

static int	dispatch_string(char **tab, char *str, char c)
{
	size_t	i;
	size_t	lines;
	size_t	was_sep;

	i = 0;
	was_sep = 1;
	lines = 0;
	while (str[i])
	{
		if (str[i] != c && was_sep)
		{
			tab[lines] = write_word(str + i, c);
			if (!tab[lines])
				return (free_array(tab), EXIT_FAILURE);
			lines++;
		}
		was_sep = (str[i] == c);
		i++;
	}
	return (0);
}

/**
 * @brief allocates a memory area and returns an array of strings
 * obtained by splitting 's' using the character 'c' as a delimiter.
 * array ends with NULL pointer
 *
 * @param s string to split
 * @param c delimiter character
 * @return char** array of new strings resulting from the split,
 * NULL if allocation fails
 */
char	**split_paths(char const *s, char c)
{
	size_t	lines;
	char	**tab;

	tab = NULL;
	lines = 0;
	if (!s)
		return (NULL);
	lines = count_lines(s, c);
	tab = malloc(sizeof(char *) * (lines + 1));
	if (!tab)
		return (NULL);
	if (dispatch_string(tab, (char *)s, c))
		return (NULL);
	if (tab)
		tab[lines] = NULL;
	return (tab);
}

void	handle_execve_failure(t_data *data, int block, char *command_path,
	char **env_array)
{
	free(command_path);
	free_array(env_array);
	free_array(data->paths);
	close_pipes(data, block);
	free_quit(data);
}
