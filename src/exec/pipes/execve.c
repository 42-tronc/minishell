/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/05/09 13:40:55 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_data *data, char *command_path);

/*
TODO

pass each command and its arg to execve
*/

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
			exec_command(data, command_path);
			return (command_path);
		}
		free(command_path);
		i++;
	}

	printf("pas trouve\n");
	return (NULL);
}

/*
Pipe -> fork
 */

void	exec_command(t_data *data, char *command_path)
{
	printf(GREEN "IN %sexec_command\n"RESET, UNDERLINE);
	(void) data;
	(void) command_path;
	// int	id;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return;
	}
	// dup2(fd du fichier, stdin);
	// id = fork();
	// printf("id = %d\n", id);
	return;
}
