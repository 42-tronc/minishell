/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/05/05 10:19:58 by croy             ###   ########lyon.fr   */
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

exit_code	get_validpath(t_data *data)
{
	int		i;
	int		error_access;
	char	*command_path;

	i = 0;
	error_access = 1;
	// Update paths in case it changed
	ft_getpaths(data);

	// command_path = ft_strjoin(data->paths[i], "ls");
	while (data->paths[i] && error_access)
	{
		command_path = ft_strjoin(data->paths[i], "loli");
		if (!command_path)
			return (MALLOC_ERROR);
		printf("checking %s\n", command_path);
		error_access = access(command_path, X_OK);
		if (!error_access)
		{
			printf(ORANGE"youpi\n"RESET);
			// return (command_path);
			break;
		}
		free(command_path);
		i++;
	}

	printf("execve avec `%s`\n", command_path);
	return (SUCCESS);

	// printf("acces_code = %d\n", error_access);
	// command_path = ft_strjoin(data->paths[i], command);
	// while (access(command_path, X_OK) == -1)
	// {
	// 	free(command_path);
	// 	command_path = ft_strjoin(data->paths[i], command);
	// 	i++;
	// }
	// execve(command_path)

}
