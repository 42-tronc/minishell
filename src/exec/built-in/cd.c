/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/04/05 12:12:36 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
NEED
`cd -`	to go back in time
`cd ~`	to go home
`cd ~~`	to go home

Si pas OLDPWD, create
get SHLVL
*/

void	ft_cd(char *path)
{
	if (!path || ft_strcmp(path, "~") == 0)
		path = getenv("HOME");
	else if (ft_strcmp(path, "-") == 0)
	{
		// printf("let's go back\n");
		// printf("OLDPWD='%s'\n", getenv("OLDPWD"));
		if (getenv("OLDPWD"))
			path = getenv("OLDPWD");
		else
		{
			perror("cd");
			printf("no old pwd, setting path to here\n");
			path = ".";
		}
	}
	printf("OG ");
	ft_pwd();

	if (chdir(path) == -1)
		perror("cd");

	printf("NEW ");
	ft_pwd();
	// else
	// {
	// 	ft_setenv("OLDPWD", ft_pwd)
	// }
}

/* int	main(int ac, char **av, char **envp)
{
	t_list	*list_envp;

	list_envp = get_envp(envp);
	(void) list_envp;
	// printf("%s\n", (char *)list_envp->content);
	// printf("getenv HOME: '%s'\n", getenv("HOME"));
	if (ac >= 2)
	{
		printf("param= '%s'\n", av[1]);
		ft_cd(av[1]);
	}
	else
		ft_cd(NULL);
	// printf("pop");
	return (0);
} */
