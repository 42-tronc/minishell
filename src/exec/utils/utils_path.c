/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:31:15 by croy              #+#    #+#             */
/*   Updated: 2023/08/11 11:40:13 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_getpaths(t_data *data)
{
	char	*paths;

	paths = ft_getenv(data->env, "PATH");
	if (!paths)
		return (EXIT_FAILURE);
	if (data->paths != NULL)
		free_array(data->paths);
	data->paths = split_paths(paths, ':');
	if (!data->paths)
		return (2);
	return (0);
}

static char	*find_path(t_data *data, char *token)
{
	int		i;
	char	*command_path;

	i = 0;
	while (data->paths[i])
	{
		(void) token;
		command_path = ft_strjoin(data->paths[i], token);
		if (!command_path)
			return (print_error(E_MALLOC, "find_path"), NULL);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Gets the path of the command passed as input
 *
 * @param data t_data struct with every var in it
 * @param input token with the command
 * @return char* path of the command or NULL if not found
 */
char	*get_validpath(t_data *data, t_token *input, char **env_array)
{
	char	*command_path;

	if (!input || !input->token)
		return (NULL);
	command_path = ft_strdup(input->token);
	if (!command_path)
		return (print_error(E_MALLOC, "get_validpath"), NULL);
	if (!ft_strcmp(command_path, ""))
		return (free(command_path), NULL);
	if (ft_strchr(input->token, '/'))
		return (command_path);
	if (ft_getpaths(data) == 1)
		return (free(command_path), NULL);
	if (ft_getpaths(data) == 2)
		return (free(command_path), \
		free_array(env_array), clean_exit(data, E_MALLOC, "ft_getpaths"), NULL);
	free(command_path);
	command_path = find_path(data, input->token);
	return (command_path);
}
