/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:31:40 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/05 14:42:46 by arthurasced      ###   ########lyon.fr   */
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

/// @brief Finds if we are insinde a simple quote or a double quote.
/// @param p Data structure
/// @param c Char to check.
void	p_quote(t_parsing *p, char c)
{
	p->quote = (p->quote + (!p->dquote && c == '\'')) % 2;
	p->dquote = (p->dquote + (!p->quote && c == '\"')) % 2;
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
	ft_tokenadd_back(tokens, ft_tokennew(word));
}

/// @brief Check if the char is a space, a pipe or a < / >.
/// @param c Char to check
/// @return 0 if it is one of the char searched for,
/// 1 if it is any other char.
int	ft_char(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

int	ft_char2(int c)
{
	if (c == '\'' || c == ' ' || c == '\"')
		return (0);
	return (1);
}

/// @brief Malloc enough memory for our symbole (|, <, <<, >, >>)
/// and add it to the linked list.
/// @param tokens Linked list of tokens.
/// @param p Data structure for the parsing.
/// @param str Input from the function readline.
void	get_symbols(t_token **tokens, t_parsing *p, char *str)
{
	char	*symbol;
	int		i;

	i = -1;
	while (str && str[++i])
		if (ft_char(str[p->i]))
			break ;
	symbol = malloc(sizeof(char) * i);
	if (!symbol)
		exit (1);
	i = -1;
	while (str && str[p->i])
	{
		if (ft_char(str[p->i]))
			break ;
		symbol[++i] = str[p->i];
		p->i++;
	}
	symbol[++i] = '\0';
	ft_tokenadd_back(tokens, ft_tokennew(symbol));
}
