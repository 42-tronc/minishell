/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:31:40 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/04 16:41:21 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_word_size(t_parsing *p, char *str, int i)
{
	int	size;

	size = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && p->dquote == 1)
			size++;
		else if (str[i] == '\"' && p->quote == 1)
			size++;
		else if (str[i] != '\'' && str[i] != '\"')
			size++;
		if (str[i] == ' ' && p->quote == 0 && p->dquote == 0)
			return (size);
		p->quote = (p->quote + (!p->dquote && str[i] == '\'')) % 2;
		p->dquote = (p->dquote + (!p->quote && str[i] == '\"')) % 2;
		i++;
	}
	return (size);
}

// Missing error managment and leaks are occuring in case of error.
void	get_next_word(t_token **tokens, t_parsing *p, char *str)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (get_word_size(p, str, p->i) + 1));
	if (!word)
		return ;
	i = -1;
	while (str && str[p->i])
	{
		if (str[p->i] == ' ' && p->quote == 0 && p->dquote == 0)
			break ;
		p->quote = (p->quote + (!p->dquote && str[p->i] == '\'')) % 2;
		p->dquote = (p->dquote + (!p->quote && str[p->i] == '\"')) % 2;
		if (p->quote == 1 && str[p->i] == '\"')
			word[++i] = '\"';
		else if (p->dquote == 1 && str[p->i] == '\'')
			word[++i] = '\'';
		else if (str[p->i] != '\'' && str[p->i] != '\"')
			word[++i] = str[p->i];
		p->i++;
	}
	word[++i] = '\0';
	ft_tokenadd_back(tokens, ft_tokennew(word));
}

void	cutting_line(t_token **tokens, t_parsing *p, char *str)
{
	p->i = 0;
	p->quote = 0;
	p->dquote = 0;
	while (str && str[p->i])
	{
		if (str[p->i] == ' ')
			p->i++;
		else if (str[p->i] == '\'' || str[p->i] == '\"' \
			|| str[p->i] != ' ')
			get_next_word(tokens, p, str);
	}
}
