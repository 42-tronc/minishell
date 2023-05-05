/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/05/05 16:14:51 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getpaths(t_data *data)
{
	char *paths;

	paths = ft_getenv(data->env, "PATH");
	data->paths = split_paths(paths, ':');
	// printf("`%s`\n", paths);
	// int i = 0;
	// while (data->paths[i])
	// {
	// 	printf("path[%d]=`%s`\n", i, data->paths[i]);
	// 	i++;
	// }
}

char	*get_validpath(t_data *data, t_token *input)
{
	int		i;
	int		error_access;
	char	*command_path;

	i = 0;
	error_access = 1;
	if (!input)
		return (NULL);
	// Update paths in case it changed
	ft_getpaths(data);

	while (data->paths[i] && error_access)
	{
		// error_access = 0;
		command_path = ft_strjoin(data->paths[i], input->token);
		if (!command_path)
			return (NULL);
		// printf("checking %s\n", command_path);
		error_access = access(command_path, X_OK);
		if (error_access == 0)
		{
			printf(ORANGE"execve avec `%s`\n"RESET, command_path);
			return (command_path);
		}
		free(command_path);
		i++;
	}

	printf("pas trouve\n");
	return (NULL);
}
