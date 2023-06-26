/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:38:39 by croy              #+#    #+#             */
/*   Updated: 2023/06/26 09:27:31 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(int code, char *source)
{
	char	*error[4];

	error[E_MALLOC] = "Malloc failed to allocate a memory space";
	error[E_DUP2] = "Dup2 failed to duplicate the file descriptor";
	error[E_PIPE] = "Pipe failed to create a pipe";
	error[E_FORK] = "For failed to create a child process";
	// error[] = "";

	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error[code], 2);
	if (source)
	{
		ft_putstr_fd(" in ", 2);
		ft_putstr_fd(source, 2);
	}
	exit(EXIT_FAILURE);
}

void	create_subshell(int (*func)(t_data*, t_token*, int), t_data *data, t_token *input, int block)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		exit_error(E_FORK, "create_subshell");
	else if (pid == 0)
	{
		if (block < data->cmd_block_count - 1 && data->cmd_block[block]->pipe_fd[0] > 0)
			close(data->cmd_block[block]->pipe_fd[0]);
		check_input(data, block);
		check_output(data, block);
		status = func(data, input, block);
		exit(status);
	}
	else
	{
		data->cmd_block[block]->pid = pid;
		if (block > 0 && data->cmd_block[block - 1]->pipe_fd[0] > 0)
			close(data->cmd_block[block - 1]->pipe_fd[0]); // Close the read end of the pipe in the child
		if (data->cmd_block[block]->pipe_fd[1] > 0 && block < data->cmd_block_count - 1)
			close(data->cmd_block[block]->pipe_fd[1]); // Close the write end of the pipe in the parent
	}
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
	int		arg_count;

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

int	check_alone(int (*func)(t_data*, t_token*, int), t_data *data, t_token *input, int block)
{
	int	status;

	status = 0;
	if (data->cmd_block_count == 1)
		status = func(data, input, block);
	else
		create_subshell(func, data, input, block);
	return (status);
}
