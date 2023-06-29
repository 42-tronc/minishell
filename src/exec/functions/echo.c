/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/06/26 09:16:35 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if string is a -n (-nnnn) of some sort
 *
 * @param str string to check
 * @return 1 if there is a -n, else 0
 */
static int	is_dash_n(char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '-')
	{
		if (str[i] == 'n')
		{
			i++;
			while (str[i] == 'n')
				i++;
			if (!str[i])
				return (1);
		}
	}
	return (0);
}

/**
 * @brief checks if there is a newline in the echo
 *
 * @remarks (*input) to deference the pointer because -> has higher precedence
 * than * and if no parenthesis, it would deference the next pointer
 * @param input t_token of the first arg
 * @return int 1 if there is a newline, else 0
 */
static int	check_newline(t_token **input)
{
	int	newline;

	newline = 1;
	while (*input && ft_strcmp((*input)->type, ARG) != 0)
		*input = (*input)->next;
	if (*input && (*input)->token && is_dash_n((*input)->token))
	{
		newline = 0;
		*input = (*input)->next;
	}
	while (*input && ft_strcmp((*input)->type, ARG) == 0
		&& is_dash_n((*input)->token))
		*input = (*input)->next;
	return (newline);
}

/**
 * @brief prints the args of echo
 *
 * @param data t_data struct with every var in it
 * @param input t_token struct with the input
 * @param block block of the pipe
 * @return int 0 if success, else 1
 */
int	ft_echo(t_data *data, t_token *input, int block)
{
	int	first;
	int	newline;

	(void)data;
	newline = check_newline(&input);
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
	return (0);
}
