/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:31:40 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/27 10:49:28 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Calculate the right size for a word,
///checking if we need to make space for the quotes (and double quotes) or not.
/// @param p Data structure for the parsing.
/// @param str Input from the function readline.
/// @param i Index reference for where we should start counting.
/// @return The size needed to allocate the correct memory.
int	get_word_size(t_parsing *p, char *str, int i)
{
	int	size;

	size = 0;
	while (str && str[i])
	{
		p->quote = (p->quote + (!p->dquote && str[i] == '\'')) % 2;
		p->dquote = (p->dquote + (!p->quote && str[i] == '\"')) % 2;
		if (str[i] == '\'' && p->dquote == 1)
			size++;
		else if (str[i] == '\"' && p->quote == 1)
			size++;
		else if (!ft_char(str[i]) && p->quote == 1)
			size++;
		else if (!ft_char(str[i]) && p->dquote == 1)
			size++;
		else if (str[i] != '\'' && str[i] != '\"' && ft_char(str[i]))
			size++;
		if (str[i] == ' ' && p->quote == 0 && p->dquote == 0)
			return (size);
		i++;
	}
	return (size);
}

/// @brief Malloc enough memory for our word, managing if we are inside quotes
/// or double quotes or both and add it to the linked list.
/// @param tokens Linked list of tokens.
/// @param p Data structure for the parsing.
/// @param str Input from the function readline.
/// @param i Counter that should ALWAYS be initialized at -1.
void	get_next_word(t_token **tokens, t_parsing *p, char *str, int i)
{
	char	*word;

	word = ft_calloc(sizeof(char), (get_word_size(p, str, p->i) + 1));
	if (!word)
		return ;
	while (str && str[p->i])
	{
		p_quote(p, str[p->i]);
		if (p->quote == 0 && p->dquote == 0 && str[p->i] == ' ')
			break ;
		else if (p->quote == 0 && p->dquote == 0 && !ft_char(str[p->i]))
			break ;
		else if (p->quote == 1 && str[p->i] == '\"')
			word[++i] = '\"';
		else if (p->dquote == 1 && str[p->i] == '\'')
			word[++i] = '\'';
		else if ((p->dquote == 1 || p->quote == 1) && !ft_char(str[p->i]))
			word[++i] = str[p->i];
		else if ((p->dquote == 1 || p->quote == 1) && str[p->i] == ' ')
			word[++i] = str[p->i];
		else if (ft_char(str[p->i]) && ft_char2(str[p->i]))
			word[++i] = str[p->i];
		p->i++;
	}
	ft_tokenadd_back(tokens, ft_tokennew(word, p, str[p->i - 1]));
}

/// @brief Malloc enough memory for our symbole (|, <, <<, >, >>)
/// and add it to the linked list.
/// @param tokens Linked list of tokens.
/// @param p Data structure for the parsing.
/// @param str Input from the function readline.
/// @param size Set to 0, I am being NORMED :DDDDDDDDD.
void	get_symbols(t_token **tokens, t_parsing *p, char *str, int size)
{
	char	*symbol;
	int		j;

	j = p->i;
	while (str && str[j] && is_symbol(str[j]))
	{
		j++;
		size++;
		if (str[j] != str[j - 1])
			break ;
	}
	symbol = malloc(sizeof(char) * (size + 1));
	if (!symbol)
		return ;
	j = 0;
	while (str && str[p->i] && is_symbol(str[p->i]))
	{
		symbol[j] = str[p->i];
		j++;
		p->i++;
		if (str[p->i] != str[p->i - 1])
			break ;
	}
	symbol[j] = '\0';
	ft_tokenadd_back(tokens, ft_tokennew(symbol, p, 0));
}
