/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:31:15 by croy              #+#    #+#             */
/*   Updated: 2023/08/10 09:34:26 by croy             ###   ########lyon.fr   */
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

/**
 * @brief Gets the path of the command passed as input
 *
 * @param data t_data struct with every var in it
 * @param input token with the command
 * @return char* path of the command or NULL if not found
 */
char	*get_validpath(t_data *data, t_token *input, char **env_array)
{
	int		i;
	char	*command_path;

	i = -1;
	command_path = ft_strdup(input->token);
	if (!input || !command_path || !ft_strcmp(command_path, ""))
		return (free(command_path), NULL);
	if (ft_strchr(input->token, '/'))
		return (command_path);
	if (ft_getpaths(data) == 1)
		return (free(command_path), NULL);
	if (ft_getpaths(data) == 2)
		return (free(command_path), \
		free_array(env_array), clean_exit(data, E_MALLOC, "ft_getpaths"), NULL);
	free(command_path);
	while (data->paths[++i])
	{
		command_path = ft_strjoin(data->paths[i], input->token);
		if (!command_path)
			return (NULL);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
	}
	return (NULL);
}
