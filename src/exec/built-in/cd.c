/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/04/06 17:31:15 by croy             ###   ########lyon.fr   */
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
void	ft_cd(char *path, char **envp)
{
	// char	*old_pwd;

	// HOME Directory
	if (!path || ft_strcmp(path, "~") == 0)
		path = ft_getenv(envp, "HOME");
	// LAST Directory
	else if (ft_strcmp(path, "-") == 0)
	{
		if (ft_getenv(envp, "OLDPWD"))
		{
			printf("found oldpwd '%s'\n", ft_getenv(envp, "OLDPWD"));
			path = ft_getenv(envp, "OLDPWD");
		}
		else
		{
			printf(RED"cd: OLDPWD not set: '%s'\n"RESET, ft_getenv(envp, "OLDPWD"));
			return;
		}
	}
	// CHANGE Directory

	// getcwd(old_pwd, BUFSIZ);
	if (chdir(path) == -1)
		perror("cd");
	else
	{
		// PWD=getcwd(cwd, BUFSIZ)
		printf("NEW ");
		ft_pwd();
	}
}

/* int	main(int ac, char **av, char **envp)
{
	printf("OG ");
	ft_pwd();
	if (ac >= 2)
	{
		// printf("\nparam= '%s'\n", av[1]);
		ft_cd(av[1], envp);
	}
	else
		ft_cd(NULL, envp);
	return (0);
} */
