/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:58:59 by croy              #+#    #+#             */
/*   Updated: 2023/06/21 10:07:05 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief redirects the output of the current cmd
 * to the outfile if there is one,
 * to the input of the next cmd if there is one,
 * or to the stdout if there is none of the above
 *
 * @param data
 * @param block
 * @return int 0 if success, exit otherwise
 */
int	check_output(t_data *data, int block)
{
	if (data->cmd_block[block]->out_fd > 0)
	{
		if (dup2(data->cmd_block[block]->out_fd, STDOUT_FILENO) == -1)
			exit_error(E_DUP2, "check_output");
		close(data->cmd_block[block]->out_fd);
	}
	else if (block < data->cmd_block_count - 1)
	{
		if (dup2(data->cmd_block[block]->pipe_fd[STDOUT_FILENO],
				STDOUT_FILENO) == -1)
			exit_error(E_DUP2, "check_output");
		close(data->cmd_block[block]->pipe_fd[STDOUT_FILENO]);
	}
	return (0);
}

/**
 * @brief redirects the input of the current cmd
 * from the infile if there is one,
 * from the here_doc if there is one,
 * from the output of the previous cmd if there is one,
 * or from the stdin if there is none of the above
 *
 * @param data
 * @param block
 * @return int 0 if success, exit otherwise
 */
int	check_input(t_data *data, int block)
{
	int	tmp_pipe[2];

	if (data->cmd_block[block]->in_fd > 0)
	{
		if (dup2(data->cmd_block[block]->in_fd, STDIN_FILENO) == -1)
			exit_error(E_DUP2, "check_input");
		close(data->cmd_block[block]->in_fd);
	}
	else if (data->cmd_block[block]->heredoc)
	{
		if ((pipe(tmp_pipe) == -1))
			exit_error(E_PIPE, "check_input");
		if (dup2(tmp_pipe[STDIN_FILENO], STDIN_FILENO) == -1)
			exit_error(E_DUP2, "check_input");
		write(tmp_pipe[STDOUT_FILENO], data->cmd_block[block]->heredoc,
			ft_strlen(data->cmd_block[block]->heredoc));
		free(data->cmd_block[block]->heredoc);
		close(tmp_pipe[STDOUT_FILENO]);
	}
	else if (block > 0 && data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] > 0)
	{
		block -= 1;
		if (dup2(data->cmd_block[block]->pipe_fd[STDIN_FILENO], \
			STDIN_FILENO) == -1)
			exit_error(E_DUP2, "check_input");
		close(data->cmd_block[block]->pipe_fd[STDIN_FILENO]);
	}
	return (0);
}
