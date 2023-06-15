/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/06/15 18:00:43 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getpaths(t_data *data)
{
	char	*paths;

	paths = ft_getenv(data->env, "PATH");
	if (!paths)
		return (1);
	data->paths = split_paths(paths, ':');
	return (0);
}

/**
 * @brief Gets the path of the command passed as input
 *
 * @param data t_data struct with every var in it
 * @param input token with the command
 * @return char* path of the command or NULL if not found
 */
char	*get_validpath(t_data *data, t_token *input)
{
	int		i;
	int		error_access;
	char	*command_path;

	i = 0;
	error_access = 1;
	if (!input)
		return (NULL);
	if (ft_strchr(input->token, '/') && !access(input->token, X_OK))
		return (input->token);
	if (ft_getpaths(data))
		return (NULL);
	while (data->paths[i] && error_access)
	{
		command_path = ft_strjoin(data->paths[i], input->token);
		if (!command_path)
			return (NULL);
		error_access = access(command_path, X_OK);
		if (!error_access)
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Counts the number of arguments + cmd to malloc
 *
 * @param input
 * @return size_t cmd + args count
 */
static size_t	_count_cmd_args(t_token *input)
{
	size_t	size;

	size = 0;
	if (ft_strcmp(input->type, CMD) == 0)
		size++;
	input = input->next;
	while (input)
	{
		if (ft_strcmp(input->type, PIPE) == 0)
			break ;
		else if (ft_strcmp(input->type, ARG) == 0)
			size++;
		input = input->next;
	}
	return (size);
}

char	**get_cmd_args(t_token *input, char *command_path)
{
	size_t	i;
	size_t	size;
	char	**array;

	if (!input)
		return (NULL);
	size = _count_cmd_args(input);
	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 1;
	input = input->next;
	array[0] = command_path;
	while (input && i < size)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			array[i] = ft_strdup(input->token);
			i++;
		}
		input = input->next;
	}
	return (array);
}

int	check_output(t_data *data, int block)
{
	if (data->cmd_block[block]->out_fd > 0)
	{
		if (dup2(data->cmd_block[block]->out_fd, STDOUT_FILENO) == -1)
			return (FAILURE);
		close(data->cmd_block[block]->out_fd);
	}
	else if (block < data->cmd_block_count - 1)
	{
		if (dup2(data->cmd_block[block]->pipe_fd[STDOUT_FILENO],
				STDOUT_FILENO) == -1)
			return (FAILURE);
		close(data->cmd_block[block]->pipe_fd[STDOUT_FILENO]);
	}
	return (0);
}

int	check_input(t_data *data, int block)
{
	int	tmp_pipe[2];

	if (data->cmd_block[block]->in_fd > 0)
	{
		if (dup2(data->cmd_block[block]->in_fd, STDIN_FILENO) == -1)
			return (FAILURE);
		close(data->cmd_block[block]->in_fd);
	}
	else if (data->cmd_block[block]->heredoc)
	{
		pipe(tmp_pipe);
		dup2(tmp_pipe[0], 0);
		write(tmp_pipe[1], data->cmd_block[block]->heredoc,
			ft_strlen(data->cmd_block[block]->heredoc));
		free(data->cmd_block[block]->heredoc);
		close(tmp_pipe[1]);
	}
	else if (block > 0 && data->cmd_block[block - 1]->pipe_fd[STDIN_FILENO] > 0)
	{
		block -= 1;
		if (dup2(data->cmd_block[block]->pipe_fd[STDIN_FILENO], STDIN_FILENO) ==
			-1)
			return (FAILURE);
		close(data->cmd_block[block]->pipe_fd[STDIN_FILENO]);
	}
	return (0);
}

int	create_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd_block_count < 1)
		return (SUCCESS);
	while (i < data->cmd_block_count - 1)
	{
		if (pipe(data->cmd_block[i]->pipe_fd) == -1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	exec_execve(t_data *data, t_token *input, int block)
{
	char	*command_path;
	char	**command_args;

	(void)block;
	command_path = get_validpath(data, input);
	command_args = get_cmd_args(input, command_path);
	execve(command_path, command_args, NULL);
	ft_putstr_fd(input->token, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

void	exec_command(t_data *data, t_token *input, int block)
{
	create_subshell(exec_execve, data, input, block);
}
