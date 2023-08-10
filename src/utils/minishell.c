/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/08/10 10:47:24 by croy             ###   ########lyon.fr   */
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
				g_ret_value = check_alone(ft_cd, data, input->next, block);
			else if (ft_strcmp(input->token, "echo") == 0)
				create_subshell(ft_echo, data, input, block);
			else if (ft_strcmp(input->token, "env") == 0)
				create_subshell(print_env, data, input, block);
			else if (ft_strcmp(input->token, "exit") == 0)
				g_ret_value = check_alone(ft_exit, data, input->next, block);
			else if (ft_strcmp(input->token, "export") == 0)
				g_ret_value = ft_export(data, input->next, block);
			else if (ft_strcmp(input->token, "pwd") == 0)
				create_subshell(ft_pwd, data, input, block);
			else if (ft_strcmp(input->token, "unset") == 0)
				g_ret_value = check_alone(ft_unset, data, input, block);
			else
				create_subshell(execve_cmd, data, input, block);
		}
		input = input->next;
	}
	close_pipes(data, block);
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
	if (argc != 1)
		return (EXIT_FAILURE);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (print_error(E_MALLOC, "main"), EXIT_FAILURE);
	fill_env(data, envp);
	while (1)
	{
		get_signal_prompt();
		getting_line(data, NULL);
		if (data->tokens && !prepare_token(data))
		{
			if (init_data(data))
				return (free_token(data->tokens), free(data->p),
					free_list(data->env), free(data), EXIT_FAILURE);
			ignore_sig();
			create_pipe(data);
			exec_dispatch(data, data->tokens);
		}
		close_all_pipes(data);
		free_in_while(data);
	}
}
