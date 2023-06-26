/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:31:40 by arthurasced       #+#    #+#             */
/*   Updated: 2023/06/26 14:13:06 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end_token(t_parsing *p, char *str)
{
	int	i;

	i = p->i;
	while (str && str[i])
	{
		p_quote(p, str[i]);
		if ((str[i] == ' ' || str[i] == '\t') && !p->quote && !p->dquote)
			return (i - 1);
		else if (is_symbol(str[i]) && is_symbol(str[i + 1]) \
		&& str[i] != str[i + 1] && !p->quote && !p->dquote)
			return (i);
		else if (!is_symbol(str[i]) && is_symbol(str[i + 1]) \
		&& !p->quote && !p->dquote)
			return (i);
		else if (is_symbol(str[i]) && !is_symbol(str[i + 1]) \
		&& !p->quote && !p->dquote)
			return (i);
		i++;
	}
	return (i - 1);
}

char	*copy_str_from_to(int from, int to, char *str)
{
	char	*copy;
	int		i;

	copy = malloc(sizeof(char) * (to - from + 2));
	if (!copy)
		return (NULL);
	i = 0;
	while (str && from <= to)
	{
		copy[i] = str[from];
		i++;
		from++;
	}
	copy[i] = '\0';
	return (copy);
}

int	cutting_line(t_token **temp, t_parsing *p, char *str)
{
	char	*token;

	while (str && str[p->i])
	{
		if (str[p->i] != ' ' && str[p->i] != '\t')
		{
			p->start = p->i;
			p->i = get_end_token(p, str);
			token = copy_str_from_to(p->start, p->i, str);
			if (!token)
				return (1);
			if (ft_tokenadd_back(temp, ft_tokennew(token)))
				return (free(token), 1);
		}
		p->i++;
	}
	return (0);
}
