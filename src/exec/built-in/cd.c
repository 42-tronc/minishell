/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maplepy <maplepy@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/04/08 16:30:07 by croy             ###   ########lyon.fr   */

/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
NEED
`cd -`	to go back in time
`cd ~`	to go home
`cd ~~`	to go home

*/

/**
 * @brief Goes into the directory specified (works with `~`)
 * `-` will go to the last directory if available.
 * `~` or `NULL` will go to the home directory
 * @param path absolute or relative path to go to.
 */
// void	ft_cd(t_env *env, t_token *input)
void	ft_cd(t_data *data, t_token *input)
{
	// (void) env;
	char	*path;
	char	previous[BUFSIZ];

	if (input && input->next)
	{
		printf("cd: too many arguments\n");
		return;
	}

	// Get the current dir to make it the OLDPWD
	getcwd(previous, BUFSIZ);

	// HOME Directory
	// if (!input->token || ft_strcmp(input->token, "~") == 0)
	ft_setenv(data->env, "OLDPWD", "/home/maplepy/git/cc/minishell/src/exec/built-in");
	// printf("OLDPWD=`%s`\n", ft_getenv(data->env, "OLDPWD"));
	ft_env(data->env);
	if (!input || ft_strcmp(input->token, "~") == 0)
		path = ft_getenv(data->env, "HOME");

	// LAST Directory
	else if (ft_strcmp(input->token, "-") == 0)
	{
		if (ft_getenv(data->env, "OLDPWD"))
		{
			path = ft_getenv(data->env, "OLDPWD");
			printf("found OLDPWD\n");
			printf("%s\n", path);
			// path = getenv("OLDPWD");
		}
		else
		{
			// printf(RED"cd: OLDPWD not set: '%s'\n"RESET, ft_getenv(env, "OLDPWD"));
			printf("cd: OLDPWD not set\n");
			return;
		}
	}

	// CHANGE Directory
	if (chdir(path) == -1)
		perror("cd");
	else
	{
		printf("OLDPWD supposed to be `%s`\n", previous);
		// ft_setenv(env, "OLDPWD", previous);
		// printf("New OLDPWD=`%s`\n", ft_getenv(env, "OLDPWD"));
	}
	printf("Moved to %s\n", path);
}

// void	ft_cd(t_env *env, char *path)
// {
// 	char	previous[BUFSIZ];

// 	getcwd(previous, BUFSIZ);
// 	// HOME Directory
// 	if (!path || ft_strcmp(path, "~") == 0)
// 		path = ft_getenv(env, "HOME");

// 	// LAST Directory
// 	else if (ft_strcmp(path, "-") == 0)
// 	{
// 		if (ft_getenv(env, "OLDPWD"))
// 		{
// 			path = ft_getenv(env, "OLDPWD");
// 			printf("%s\n", path);
// 			// path = getenv("OLDPWD");
// 		}
// 		else
// 		{
// 			// printf(RED"cd: OLDPWD not set: '%s'\n"RESET, ft_getenv(env, "OLDPWD"));
// 			printf("cd: OLDPWD not set\n");
// 			return;
// 		}
// 	}

// 	// CHANGE Directory
// 	if (chdir(path) == -1)
// 		perror("cd");
// 	else
// 	{
// 		ft_setenv(env, "OLDPWD", previous);
// 		printf("New OLDPWD=`%s`\n", ft_getenv(env, "OLDPWD"));
// 	}
// }
