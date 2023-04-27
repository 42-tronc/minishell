/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:19:54 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/08 16:50:19 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	even_quote(char *str)
{
	int	i;
	int	nb_quote;
	int	nb_dquote;

	nb_quote = 0;
	nb_dquote = 0;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			nb_quote++;
		if (str[i] == '\"')
			nb_dquote++;
	}
	if (nb_quote % 2 != 0 || nb_dquote % 2 != 0)
	{
		free(str);
		printf("error - quotes or double quotes not closed correctly\n");
		exit (1);
	}
}

void	right_symbols(t_parsing *p, char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		p->quote = (p->quote + (!p->dquote && str[i] == '\'')) % 2;
		p->dquote = (p->dquote + (!p->quote && str[i] == '\"')) % 2;
		if (i >= 1 && p->quote == 0 && p->dquote == 0)
		{
			if (str[i] == '|' && str[i - 1] == '|')
			{
				printf ("error ||\n");
				exit (1);
			}
		}
		if (i >= 2 && p->quote == 0 && p->dquote == 0)
		{
			if ((str[i] == '>' && str[i - 1] == '>' && str[i - 2] == '>')
				|| (str[i] == '<' && str[i - 1] == '<' && str[i - 2] == '<'))
			{
				printf ("error <<< or >>>\n");
				exit (1);
			}
		}
	}
}

/// @brief Choose what action to do based on the char in a string.
/// @param tokens Linked list of tokens.
/// @param p Data structure for the parsing.
/// @param str Input from the function readline.
void	cutting_line(t_token **tokens, t_parsing *p, char *str)
{
	while (str && str[p->i])
	{
		if (str[p->i] == ' ')
			p->i++;
		else if (ft_char(str[p->i]))
			get_next_word(tokens, p, str, -1);
		else
		{
			get_symbols(tokens, p, str);
		}
	}
}

t_token	*getting_line(t_parsing *p)
{
	t_token	*tokens;
	char	*str;

	tokens = NULL;
	str = readline("minishell>");
	p->i = 0;
	p->quote = 0;
	p->dquote = 0;
	even_quote(str);
	right_symbols(p, str);
	cutting_line(&tokens, p, str);
	return (free(str), tokens);
}
