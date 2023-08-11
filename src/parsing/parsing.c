/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:19:54 by arthurasced       #+#    #+#             */
/*   Updated: 2023/07/24 07:46:12 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	even_quote(t_parsing *p, char *str)
{
	int	i;
	int	nb_quote;
	int	nb_dquote;

	nb_quote = 0;
	nb_dquote = 0;
	i = -1;
	while (str && str[++i])
	{
		p_quote(p, str[i]);
		if (p->dquote == 0 && str[i] == '\'')
			nb_quote++;
		else if (p->quote == 0 && str[i] == '\"')
			nb_dquote++;
	}
	if (nb_quote % 2 || nb_dquote % 2)
	{
		ft_putendl_fd("quotes or double quotes aren't closed correctly", 2);
		return (0);
	}
	return (1);
}

int	triple_symbol(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		return (1);
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		return (1);
	if (str[i] == '|' && str[i + 1] == '|')
		return (1);
	return (0);
}

int	right_symbols(t_parsing *p, char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		p_quote(p, str[i]);
		if (p->quote == 0 && p->dquote == 0 && triple_symbol(str, i))
		{
			ft_putstr_fd(" syntax error near unexpected token `", 2);
			write(2, &str[i], 1);
			ft_putendl_fd("'", 2);
			g_ret_value = 2;
			return (0);
		}
	}
	return (1);
}

void	set_parsing_info(t_data *data)
{
	data->p->i = 0;
	data->p->quote = 0;
	data->p->dquote = 0;
}

int	getting_line(t_data *data, char *str)
{
	data->tokens = NULL;
	data->p = ft_calloc(1, sizeof(t_parsing));
	if (!data->p)
	{
		free_list(data->env);
		free(data);
		print_error(E_MALLOC, "ft_calloc in getting_line");
		exit(1);
	}
	str = readline(BOLD WHITE"minishell> "RESET);
	if (!str)
		exit_program(data);
	if (str && str[0] != '\0')
	{
		add_history(str);
		set_parsing_info(data);
		if (!even_quote(data->p, str) || !right_symbols(data->p, str))
		{
			g_ret_value = 2;
			return (free(str), 1);
		}
		if (cutting_line(data, &data->tokens, data->p, str))
			return (free(str), 1);
	}
	return (free(str), 0);
}
