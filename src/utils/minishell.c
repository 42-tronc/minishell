/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/06/30 09:27:27 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ret_value;

static void	check_command(t_data *data, t_token *input, int block)
{
	while (input && input->pipe_block == block)
	{
		if (input->type && ft_strcmp(input->type, CMD) == 0)
		{
			if (ft_strcmp(input->token, "cd") == 0)
				g_ret_value = ft_cd(data, input->next, block);
			else if (ft_strcmp(input->token, "echo") == 0)
				create_subshell(ft_echo, data, input, block);
			else if (ft_strcmp(input->token, "env") == 0)
				create_subshell(print_env, data, input, block);
			else if (ft_strcmp(input->token, "exit") == 0)
				check_alone(ft_exit, data, input->next, block);
			else if (ft_strcmp(input->token, "export") == 0)
				g_ret_value = ft_export(data, input->next, block);
			else if (ft_strcmp(input->token, "pwd") == 0)
				create_subshell(ft_pwd, data, input, block);
			else if (ft_strcmp(input->token, "unset") == 0)
				g_ret_value = ft_unset(&data->env, input, block);
			else
				create_subshell(execve_cmd, data, input, block);
		}
		input = input->next;
	}
}

void	exec_code(t_data *data)
{
	int	block;
	int	status;
	int	statuscode;

	block = 0;
	status = -1;
	statuscode = 0;
	while (block < data->cmd_ct)
	{
		waitpid(data->cmd_block[block]->pid, &status, 0);
		block++;
	}
	if (WIFEXITED(status))
		statuscode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		handle_signals(WTERMSIG(status));
	}
	if (!WIFSIGNALED(status) && status != -1)
		g_ret_value = statuscode;
}

static void	close_pipes(t_data *data, int block)
{
	if (block > 0 && data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] > 0)
	{
		close(data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO]);
		data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] = -3;
	}
	if (block < data->cmd_ct - 1
		&& data->cmd_block[block]->pipe_fd[STDOUT_FILENO] > 0)
	{
		close(data->cmd_block[block]->pipe_fd[STDOUT_FILENO]);
		data->cmd_block[block]->pipe_fd[STDOUT_FILENO] = -3;
	}
}

void	exec_dispatch(t_data *data, t_token *input)
{
	int	error;
	int	block;

	error = 0;
	block = 0;
	while (input && block < data->cmd_ct)
	{
		if (check_heredoc(data, input, block))
			return ;
		error = check_infile(data, input, block);
		if (!error)
			error = check_outfile(data, input, block);
		if (!error)
			check_command(data, input, block);
		else
			close_pipes(data, block);
		if (block == data->cmd_ct - 1 && error)
			g_ret_value = 1;
		if (block == data->cmd_ct - 1 && error)
			return ;
		block++;
		while (block > input->pipe_block && input->next)
			input = input->next;
	}
	exec_code(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (argc != 1 || !data)
		return (1);
	fill_env(data, envp);
	while (1)
	{
		get_signal_prompt();
		getting_line(data);
		if (data->tokens && !prepare_token(data))
		{
			if (init_data(data))
				free_quit(data);
			ignore_sig();
			create_pipe(data);
			exec_dispatch(data, data->tokens);
			free_cmd_block(data);
		}
		if (data->tokens)
			free_token(data->tokens);
		free(data->p);
	}
	free_list(data->env);
}
