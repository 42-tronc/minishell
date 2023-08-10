/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 07:54:16 by croy              #+#    #+#             */
/*   Updated: 2023/08/10 09:34:26 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alone(int (*func)(t_data *, t_token *, int), t_data *data,
		t_token *input, int block)
{
	int	status;

	status = 0;
	if (data->cmd_ct == 1)
		status = func(data, input, block);
	else
		create_subshell(func, data, input, block);
	return (status);
}

void	ignore_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	check_io(t_data *data, int block)
{
	check_input(data, block);
	check_output(data, block);
	close_all_pipes(data);
}

void	create_subshell(int (*func)(t_data *, t_token *, int), t_data *data,
		t_token *input, int block)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		clean_exit(data, E_FORK, "create_subshell");
	else if (pid == 0)
	{
		get_signal_exec();
		if (block < data->cmd_ct - 1 && data->cmd_block[block]->pipe_fd[0] > 0)
			close_fd(data->cmd_block[block]->pipe_fd[0]);
		check_io(data, block);
		status = func(data, input, block);
		free_quit(data);
		rl_clear_history();
		exit(status);
	}
	else
	{
		data->cmd_block[block]->pid = pid;
		close_parent_fd(data, block);
	}
}
