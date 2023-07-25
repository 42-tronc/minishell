/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:31:15 by croy              #+#    #+#             */
/*   Updated: 2023/06/26 12:29:47 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_getpaths(t_data *data)
{
	char	*paths;

	paths = ft_getenv(data->env, "PATH");
	if (!paths)
		return (1);
	data->paths = split_paths(paths, ':');
	if (!data->paths)
		exit_error(data, E_MALLOC, "ft_getpaths");
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
	char	*command_path;

	i = 0;
	command_path = ft_strdup(input->token);
	if (!input || !ft_strcmp(input->token, ""))
		return (NULL);
	if (ft_strchr(input->token, '/'))
		return (command_path);
	if (ft_getpaths(data))
		return (NULL);
	free(command_path);
	while (data->paths[i])
	{
		command_path = ft_strjoin(data->paths[i], input->token);
		if (!command_path)
			return (NULL);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		i++;
		free(command_path);
	}
	return (NULL);
}
