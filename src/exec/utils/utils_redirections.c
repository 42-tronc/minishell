/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:58:59 by croy              #+#    #+#             */
/*   Updated: 2023/08/10 09:34:26 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc(t_data *data, t_cmd_block *cmd_block)
{
	int	tmp_pipe[2];

	if (pipe(tmp_pipe) == -1)
		clean_exit(data, E_PIPE, "handle_heredoc");
	if (dup2(tmp_pipe[STDIN_FILENO], STDIN_FILENO) == -1)
	{
		close_fd(tmp_pipe[STDIN_FILENO]);
		close_fd(tmp_pipe[STDOUT_FILENO]);
		clean_exit(data, E_DUP2, "handle_heredoc");
	}
	write(tmp_pipe[STDOUT_FILENO], cmd_block->heredoc,
		ft_strlen(cmd_block->heredoc));
	close_fd(tmp_pipe[STDOUT_FILENO]);
	close_fd(tmp_pipe[STDIN_FILENO]);
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
void	check_input(t_data *data, int block)
{
	if (data->cmd_block[block]->in_fd > 0)
	{
		if (dup2(data->cmd_block[block]->in_fd, STDIN_FILENO) == -1)
		{
			close_fd(data->cmd_block[block]->in_fd);
			clean_exit(data, E_DUP2, "check_input");
		}
		close_fd(data->cmd_block[block]->in_fd);
	}
	else if (data->cmd_block[block]->heredoc_here)
		handle_heredoc(data, data->cmd_block[block]);
	else if (block > 0 && data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] > 0)
	{
		block -= 1;
		if (dup2(data->cmd_block[block]->pipe_fd[STDIN_FILENO],
				STDIN_FILENO) == -1)
		{
			close_fd(data->cmd_block[block]->pipe_fd[STDIN_FILENO]);
			clean_exit(data, E_DUP2, "check_input");
		}
		close_fd(data->cmd_block[block]->pipe_fd[STDIN_FILENO]);
	}
}

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
void	check_output(t_data *data, int block)
{
	if (data->cmd_block[block]->out_fd > 0)
	{
		if (dup2(data->cmd_block[block]->out_fd, STDOUT_FILENO) == -1)
		{
			close_fd(data->cmd_block[block]->out_fd);
			clean_exit(data, E_DUP2, "check_output");
		}
		close_fd(data->cmd_block[block]->out_fd);
	}
	else if (block < data->cmd_ct - 1)
	{
		if (dup2(data->cmd_block[block]->pipe_fd[STDOUT_FILENO],
				STDOUT_FILENO) == -1)
		{
			close_fd(data->cmd_block[block]->pipe_fd[STDOUT_FILENO]);
			clean_exit(data, E_DUP2, "check_output");
		}
		close_fd(data->cmd_block[block]->pipe_fd[STDOUT_FILENO]);
	}
}

static void	error_close_pipes(t_data *data, int i)
{
	while (i >= 0)
	{
		close_fd(data->cmd_block[i]->pipe_fd[STDIN_FILENO]);
		close_fd(data->cmd_block[i]->pipe_fd[STDOUT_FILENO]);
		i--;
	}
}

int	create_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd_ct < 1)
		return (EXIT_SUCCESS);
	while (i < data->cmd_ct - 1)
	{
		if (pipe(data->cmd_block[i]->pipe_fd) == -1)
		{
			error_close_pipes(data, i - 1);
			clean_exit(data, E_PIPE, "create_pipe");
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
