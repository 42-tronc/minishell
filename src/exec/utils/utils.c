/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:38:39 by croy              #+#    #+#             */
/*   Updated: 2023/06/19 15:20:16 by croy             ###   ########lyon.fr   */
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

	// should prob print to fd 2
	// printf(RED"Error: %s\n"RESET, error[code]);
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
	{
		perror("fork");
		return ; // will need to exit here
	}
	else if (pid == 0)
	{
		if (check_input(data, block) == EXIT_FAILURE)
			return ; // dup2 failed exit here
		if (check_output(data, block) == EXIT_FAILURE)
			return ; // dup2 failed exit here
		status = func(data, input, block);
		exit(status);
	}
	else
	{
		data->cmd_block[block]->pid = pid;
		if (data->cmd_block[block]->pipe_fd[0] > 0 && block > 0)
			close(data->cmd_block[block - 1]->pipe_fd[0]); // Close the read end of the pipe in the child
		if (data->cmd_block[block]->pipe_fd[1] > 0 && block < data->cmd_block_count - 1)
			close(data->cmd_block[block]->pipe_fd[1]); // Close the write end of the pipe in the parent
	}
}