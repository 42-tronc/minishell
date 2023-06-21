/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/06/21 12:47:06 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// debug functions
void	print_tokens_linked_list(t_token *head)
{
	t_token	*temp;
	int		i;

	temp = head;
	// last = NULL;
	i = 0;
	while (temp != NULL)
	{
		printf("Type : %s && token[%d]:'%s' FROM EXPAND?=%d\n",temp->type, i++, temp->token, temp->from_expand);
		// if (temp->next == NULL)
		// 	last = temp;
		temp = temp->next;
	}
	// while (last)
	// {
	// 	printf("token prev:%s\n", last->token_id);
	// 	last = last->prev;
	// }
}

// might need to change the export and set to only print if there is a value, if not it is a export
void	check_command(t_data *data, t_token *input, int block)
{
	while (input && input->pipe_block == block)
	{
		if (input->type && ft_strcmp(input->type, CMD) == 0)
		{
			if (ft_strcmp(input->token, "cd") == 0)
				data->status = ft_cd(data, input->next, block);
			else if (ft_strcmp(input->token, "echo") == 0)
				ft_echo(data, input->next, block);
			else if (ft_strcmp(input->token, "env") == 0)
				ft_env(data, input, block);
			else if (ft_strcmp(input->token, "exit") == 0)
				// ft_exit(data, input->next);
				check_alone(ft_exit, data, input->next, block);
			else if (ft_strcmp(input->token, "export") == 0)
				data->status = ft_export(data, input->next, block);
			else if (ft_strcmp(input->token, "pwd") == 0)
				create_subshell(ft_pwd, data, input, block);
			else if (ft_strcmp(input->token, "unset") == 0)
				ft_unset(&data->env, input, block);
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
	int statuscode;

	block = 0;
	status = -1; // Variable to store the return status of the child process
	while (block < data->cmd_block_count)
	{
		waitpid(data->cmd_block[block]->pid, &status, 0);
		block++;
	}
	// data->status = WEXITSTATUS(status);
	// printf("wexit = %d\n", data->status);
	if (WIFEXITED(status)) {
		statuscode = WEXITSTATUS(status);
		// if (statuscode != 0)
			// printf(RED"failure with %d\n" RESET, statuscode);
			// printf(BOLD GREEN "success\n" RESET);
			// printf(BOLD GREEN "%s: %ssuccess\n" RESET, input->token, NO_BOLD);
		// else
	}
	if (status != -1)
		data->status = statuscode;
}

static void	close_pipes(t_data *data, int block)
{
	if (block > 0 && data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] > 0)
	{
		close(data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO]);
		data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] = -3;
	}
	if (block < data->cmd_block_count - 1 && data->cmd_block[block]->pipe_fd[STDOUT_FILENO] > 0)
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
	// printf("cmd block count = %d\n", data->cmd_block_count);
	while (input && block < data->cmd_block_count)
	{
		// printf(RED "block=%d\ncurrent block %d\n" RESET, block, input->pipe_block);
		check_heredoc(data, input, block);
		error = check_infile(data, input, block);
		if (!error)
			error = check_outfile(data, input, block);
		if (!error)
			check_command(data, input, block); // will be changed
		else
			close_pipes(data, block);
		if (block == data->cmd_block_count - 1 && error)
		{
			data->status = 1;
			return ;
		}
		block++;
		while (block > input->pipe_block && input->next)
			input = input->next;
	}
	exec_code(data);
}

// will need to get the return value to somewhere
int	init_data(t_data *data)
{
	int		i;
	t_token	*temp;

	temp = data->tokens;
	data->cmd_block_count = 1;
	while (temp)
	{
		if (!ft_strcmp(temp->type, PIPE))
			data->cmd_block_count++;
		temp = temp->next;
	}
	data->cmd_block = ft_calloc(data->cmd_block_count + 1, sizeof(t_cmd_block*));
	if (!data->cmd_block)
		return (E_MALLOC);
	i = 0;
	while (i < data->cmd_block_count)
	{
		data->cmd_block[i] = ft_calloc(1, sizeof(t_cmd_block));
		if (!data->cmd_block[i])
			return (E_MALLOC); // exit here
		data->cmd_block[i]->in_fd = -2;
		data->cmd_block[i]->out_fd = -2;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data 	*data;

	(void)argv;
	if (argc != 1)
		return ((void)printf("Don't put args !\n"), 1);
	data = ft_calloc(1, sizeof(t_data));
	data->env = fill_env(envp);
	get_signal();
	while (1)
	{
		getting_line(data);
		if (data->tokens && !prepare_token(data))
		{
			if (init_data(data))
				exit(EXIT_FAILURE);
			create_pipe(data);
			exec_dispatch(data, data->tokens);
		}
		free_token(data->tokens);
		free(data->p);
	}
	if (data->env)
		free_list(data->env);
	return (0);
}
