/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:38:39 by croy              #+#    #+#             */
/*   Updated: 2023/08/10 09:41:53 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int code, char *source)
{
	char	*error[4];

	error[E_MALLOC] = "Malloc failed to allocate a memory space";
	error[E_DUP2] = "Dup2 failed to duplicate the file descriptor";
	error[E_PIPE] = "Pipe failed to create a pipe";
	error[E_FORK] = "Fork failed to create a child process";
	write(2, "\e[31;1mError: \e[22m", 19);
	write(2, error[code], ft_strlen(error[code]));
	if (source)
	{
		write(2, " in \e[1m", 8);
		write(2, source, ft_strlen(source));
		write(2, "\e[0m\n", 5);
	}
}

void	clean_exit(t_data *data, int code, char *source)
{
	print_error(code, source);
	close_all_pipes(data);
	free_quit(data);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

/**
 * @brief Counts the number of arguments in the input
 * @remark The command is not counted as an argument
 *
 * @param input t_token with the first argument
 * @param block block of the pipe
 * @return int number of arguments
 */
int	count_arguments(t_token *input)
{
	int	arg_count;

	arg_count = 0;
	while (input)
	{
		if (ft_strcmp(input->type, PIPE) == 0)
			break ;
		if (ft_strcmp(input->type, ARG) == 0)
			arg_count++;
		input = input->next;
	}
	return (arg_count);
}

/**
 * @brief swaps the values of two char pointers
 *
 * @param current first char pointer
 * @param next second char pointer
 */
void	swap_var(char **current, char **next)
{
	char	*tmp;

	tmp = *current;
	*current = *next;
	*next = tmp;
}
