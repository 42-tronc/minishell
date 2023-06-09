/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/06/09 11:29:01 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if a newline is needed by looking for any '-n' or '-nnnn...'
 *
 * @param str string to check
 * @return int 1 if needed so no `-n` found, else 0
 */
static int	need_newline(char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '-')
	{
		if (str && str[1] == 'n')
		{
			i++;
			while (str[i] && str[i] == 'n')
				i++;
			if (!str[i])
				return (0);
		}
	}
	return (1);
}

void	echo_print(t_data *data, t_token *input, int block)
{
	(void) data;
	int	first;
	int	newline;

	newline = 1;
	if (input && input->token && !need_newline(input->token))
	{
		newline = 0;
		input = input->next;
	}
	while (input && input->token && !need_newline(input->token))
		input = input->next;
	first = 1;
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			write(STDOUT_FILENO, input->token, ft_strlen(input->token));
			first = 0;
		}
		if (input->next && ft_strcmp(input->next->type, ARG) == 0 && !first)
			write(STDOUT_FILENO, " ", 1);
		input = input->next;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief print a string or an array of strings
 *
 * @param ac nb of args passed
 * @param av array of args to print
 */
void	ft_echo(t_data *data, t_token *input, int block)
{
	create_subshell(echo_print, data, input, block);
}
