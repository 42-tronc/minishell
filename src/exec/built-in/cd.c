/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/06/12 10:25:33 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_path(t_data *data, t_token *input)
{
	char	*path;

	// HOME Directory
	if (!input || ft_strcmp(input->token, "~") == 0)
		path = ft_getenv(data->env, "HOME");

	// LAST Directory
	else if (ft_strcmp(input->token, "-") == 0)
	{
		if (ft_getenv(data->env, "OLDPWD"))
		{
			path = ft_getenv(data->env, "OLDPWD");
		}
		else
		{
			printf("cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		path = input->token;
	return (path);
}

/**
 * @brief Goes into the directory specified (works with `~`)
 * `-` will go to the last directory if available.
 * `~` or `NULL` will go to the home directory
 * @param path absolute or relative path to go to.
 */
void	ft_cd(t_data *data, t_token *input)
{
	char	*path;
	char	previous[BUFSIZ];

	if (input && input->next)
	{
		printf("cd: too many arguments\n");
		return;
	}

	// Get the current dir to make it the OLDPWD
	getcwd(previous, BUFSIZ);
	path = get_cd_path(data, input);
	printf("path = `%s`\n", path);

	if (!path)
		return;
	if (chdir(path) == -1)
		perror("cd");
	else
	{
		ft_setenv(data->env, "OLDPWD", previous);
		printf("New OLDPWD\t%s\n", ft_getenv(data->env, "OLDPWD"));
	}
	printf("New path\t");
	ft_pwd();
	// printf("Moved to %s\n", path);
}
