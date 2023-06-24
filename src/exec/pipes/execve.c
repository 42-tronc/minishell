/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/06/24 20:40:22 by croy             ###   ########lyon.fr   */
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
		exit_error(E_MALLOC, "get_cmd_args");
	i = 1;
	input = input->next;
	array[0] = command_path;
	while (input && i < size)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			array[i] = ft_strdup(input->token);
			if (!array[i])
				exit_error(E_MALLOC, "get_cmd_args");
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

char	**env_to_array(t_env *env)
{
	int		i;
	int		size;
	char	**array;

	size = env_size(env);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		exit_error(E_MALLOC, "env_to_array 1");
	i = 0;
	while (env)
	{
		// array[i] = ft_strjoin(env->var, env->value);
		array[i] = ft_strjoin(env->var, "=");
		if (!array[i] && env->var)
		{
			free_array(array);
			exit_error(E_MALLOC, "env_to_array 2");
		}
		array[i] = ft_strjoin(array[i], env->value);
		if (!array[i] && env->value)
		{
			free_array(array);
			exit_error(E_MALLOC, "env_to_array 3");
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

int	execve_cmd(t_data *data, t_token *input, int block)
{
	char	*command_path;
	char	**command_args;
	char	**env_array;

	(void)block;
	env_array = env_to_array(data->env);
	command_path = get_validpath(data, input);
	// if (!command_path)
	// 	return (EXIT_FAILURE);
	command_args = get_cmd_args(input, command_path);
	if (!command_args)
		return (EXIT_FAILURE);
	execve(command_path, command_args, env_array);
	free_array(env_array);
	free_array(command_args);
	ft_putstr_fd(input->token, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}
