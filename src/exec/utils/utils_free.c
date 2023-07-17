/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:43:01 by croy              #+#    #+#             */
/*   Updated: 2023/06/30 13:04:04 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **env_array)
{
	size_t	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	free_cmd_block(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_ct)
	{
		free(data->cmd_block[i]->heredoc);
		free(data->cmd_block[i]);
		i++;
	}
	free(data->cmd_block);
}

void	free_quit(t_data *data)
{
	free_token(data->tokens);
	free_cmd_block(data);
	free(data->p);
	free_list(data->env);
	free(data);
}

void	close_parent_fd(t_data *data, int block)
{
	if (block > 0 && data->cmd_block[block - 1]->pipe_fd[0] > 0)
		close(data->cmd_block[block - 1]->pipe_fd[0]);
	if (data->cmd_block[block]->pipe_fd[1] > 0 && block < data->cmd_ct - 1)
		close(data->cmd_block[block]->pipe_fd[1]);
	if (data->cmd_block[block]->in_fd > 0)
		close(data->cmd_block[block]->in_fd);
	if (data->cmd_block[block]->out_fd > 0)
		close(data->cmd_block[block]->out_fd);
}
