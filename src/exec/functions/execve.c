/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/06/29 07:56:36 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Put the cmd and its arguments in an array
 * @remark The first argument is the command itself
 * @remark The last argument is NULL
 *
 * @param input t_token struct with the input
 * @param command_path path of the command
 * @return char** array with the command and its arguments
 */
char	**get_cmd_args(t_data *data, t_token *input, char *command_path)
{
	size_t	i;
	size_t	size;
	char	**array;

	if (!input)
		return (NULL);
	size = count_arguments(input) + 1;
	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		exit_error(data, E_MALLOC, "get_cmd_args");
	i = 1;
	input = input->next;
	array[0] = command_path;
	while (input && i < size)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			array[i] = ft_strdup(input->token);
			if (!array[i])
				exit_error(data, E_MALLOC, "get_cmd_args");
			i++;
		}
		input = input->next;
	}
	return (array);
}

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**env_to_array(t_data *data, t_env *env, int size, char *copy)
{
	int		i;
	char	**array;

	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		exit_error(data, E_MALLOC, "env_to_array 1");
	i = 0;
	while (env)
	{
		copy = ft_strjoin(env->var, "=");
		if (!copy && env->var)
			free_array(array);
		if (!copy && env->var)
			exit_error(data, E_MALLOC, "env_to_array 2");
		array[i] = ft_strjoin(copy, env->value);
		free(copy);
		if (!array[i] && env->value)
			free_array(array);
		if (!array[i] && env->value)
			exit_error(data, E_MALLOC, "env_to_array 3");
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

static int	is_executable_file(t_token *input, char *path)
{
	struct stat	file_stat;

	if (!path || stat(path, &file_stat) == -1)
	{
		write(STDERR_FILENO, input->token, ft_strlen(input->token));
		if (!path)
			write(STDERR_FILENO, ": command not found\n", 21);
		else
			write(STDERR_FILENO, ": no such file or directory\n", 28);
		return (127);
	}
	else if (S_ISDIR(file_stat.st_mode) || access(path, X_OK) == -1)
	{
		write(STDERR_FILENO, input->token, ft_strlen(input->token));
		if (S_ISDIR(file_stat.st_mode))
			ft_putendl_fd(": is a directory", STDERR_FILENO);
		else
			ft_putendl_fd(": permission denied", STDERR_FILENO);
		return (126);
	}
	return (0);
}

int	execve_cmd(t_data *data, t_token *input, int block)
{
	int		status;
	char	*command_path;
	char	**command_args;
	char	**env_array;

	(void)block;
	status = 0;
	env_array = env_to_array(data, data->env, env_size(data->env), NULL);
	command_path = get_validpath(data, input);
	status = is_executable_file(input, command_path);
	if (status == EXIT_SUCCESS)
	{
		command_args = get_cmd_args(data, input, command_path);
		if (!command_args)
			return (EXIT_FAILURE);
		execve(command_path, command_args, env_array);
		free_array(command_args);
	}
	else
		free(command_path);
	free_array(env_array);
	return (status);
}