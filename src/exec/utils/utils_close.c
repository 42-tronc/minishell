/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:43:43 by croy              #+#    #+#             */
/*   Updated: 2023/08/10 09:48:04 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > 0)
	{
		close(fd);
		fd = -3;
	}
}

void	close_all_pipes(t_data *data)
{
	int	i;

	i = 0;
	if (!data->cmd_block)
		return ;
	while (i < data->cmd_ct)
	{
		close_fd(data->cmd_block[i]->pipe_fd[0]);
		close_fd(data->cmd_block[i]->pipe_fd[1]);
		i++;
	}
}

void	close_parent_fd(t_data *data, int block)
{
	if (block > 0 && data->cmd_block[block - 1]->pipe_fd[0] > 0)
		close_fd(data->cmd_block[block - 1]->pipe_fd[0]);
	if (data->cmd_block[block]->pipe_fd[1] > 0 && block < data->cmd_ct - 1)
		close_fd(data->cmd_block[block]->pipe_fd[1]);
	if (data->cmd_block[block]->in_fd > 0)
		close_fd(data->cmd_block[block]->in_fd);
	if (data->cmd_block[block]->out_fd > 0)
		close_fd(data->cmd_block[block]->out_fd);
}

void	close_pipes(t_data *data, int block)
{
	if (block > 0 && data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] > 0)
	{
		close_fd(data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO]);
		data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] = -3;
	}
	if (block < data->cmd_ct - 1
		&& data->cmd_block[block]->pipe_fd[STDOUT_FILENO] > 0)
	{
		close_fd(data->cmd_block[block]->pipe_fd[STDOUT_FILENO]);
		data->cmd_block[block]->pipe_fd[STDOUT_FILENO] = -3;
	}
	if (data->cmd_block[block]->out_fd > 0)
		close(data->cmd_block[block]->out_fd);
	if (data->cmd_block[block]->in_fd > 0)
		close_fd(data->cmd_block[block]->in_fd);
}
