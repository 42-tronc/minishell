/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/06/19 17:16:05 by croy             ###   ########lyon.fr   */
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
			return (NULL); // Need to exit here
		error_access = access(command_path, X_OK);
		if (!error_access)
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Put the cmd and its arguments in an array
 * @remark The first argument is the command itself
 * @remark The last argument is NULL
 *
 * @param input t_token struct with the input
 * @param command_path path of the command
 * @return char** array with the command and its arguments
 */
char	**get_cmd_args(t_token *input, char *command_path)
{
	size_t	i;
	size_t	size;
	char	**array;

	if (!input)
		return (NULL);
	size = count_arguments(input) + 1;
	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL); // exit here
	i = 1;
	input = input->next;
	array[0] = command_path;
	while (input && i < size)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			array[i] = ft_strdup(input->token);
			if (!array[i])
				exit (EXIT_FAILURE); // exit here
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
			return (EXIT_FAILURE);
		close(data->cmd_block[block]->out_fd);
	}
	else if (block < data->cmd_block_count - 1)
	{
		if (dup2(data->cmd_block[block]->pipe_fd[STDOUT_FILENO],
				STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
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
			return (EXIT_FAILURE);
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
			return (EXIT_FAILURE);
		close(data->cmd_block[block]->pipe_fd[STDIN_FILENO]);
	}
	return (0);
}

int	create_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd_block_count < 1)
		return (EXIT_SUCCESS);
	while (i < data->cmd_block_count - 1)
	{
		if (pipe(data->cmd_block[i]->pipe_fd) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	env_size(t_env *env)
{
	int size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	free_array(char **env_array)
{
	char	**current;

	if (!env_array)
		return ;
	current = env_array;
	while (*current)
	{
		free(*current);
		current++;
	}
	free(env_array);
}

char	**env_to_array(t_env *env)
{
	int		i;
	int		size;
	char	**array;

	size = env_size(env);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL); // exit here
	i = 0;
	while (env)
	{
		// array[i] = ft_strjoin(env->var, env->value);
		array[i] = ft_strjoin(env->var, "=");
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		array[i] = ft_strjoin(array[i], env->value);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	array[i] = NULL;
	// char **current = array;
	// while (*current)
	// {
	// 	printf("%s\n", *current);
	// 	current++;
	// }
	return (array);
}

int	exec_cmd(t_data *data, t_token *input, int block)
{
	char	*command_path;
	char	**command_args;
	char	**env_array;

	(void) block;
	env_array = env_to_array(data->env);
	command_path = get_validpath(data, input);
	// if (!command_path)
	// 	return (EXIT_FAILURE);
	command_args = get_cmd_args(input, command_path);
	if (!command_args)
		return (EXIT_FAILURE);
	printf("going to run %s\n", command_path);
	execve(command_path, command_args, env_array);
	free_array(env_array);
	free_array(command_args);
	ft_putstr_fd(input->token, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

void	exec_command(t_data *data, t_token *input, int block)
{
	create_subshell(exec_cmd, data, input, block);
}
