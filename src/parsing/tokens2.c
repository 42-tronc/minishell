/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:36:59 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/27 10:12:46 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

/// @brief Finds if we are insinde a simple quote or a double quote.
/// @param p Data structure
/// @param c Char to check.
void	p_quote(t_parsing *p, char c)
{
	p->quote = (p->quote + (!p->dquote && c == '\'')) % 2;
	p->dquote = (p->dquote + (!p->quote && c == '\"')) % 2;
}
