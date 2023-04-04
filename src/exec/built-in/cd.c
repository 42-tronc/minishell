/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/04/04 16:35:57 by croy             ###   ########lyon.fr   */
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
	if (getenv("OLDPWD"))
		printf("OLDPWD='%s'\n", getenv("OLDPWD"));
	// Change to home directory
	if (!path || ft_strcmp(path, "~") == 0)
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd");
	}
	else
	{
		// Change to the specified directory
		if (chdir(path) == -1)
			perror("cd");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list	*list_envp;

	list_envp = get_envp(envp);
	(void) list_envp;
	// printf("%s\n", (char *)list_envp->content);
	// printf("getenv HOME='%s'\n", getenv("HOME"));
	if (ac >= 2)
	{
		printf("param= '%s'\n", av[1]);
		ft_cd(av[1]);
	}
	else
		ft_cd(NULL);
	ft_pwd();
	printf("pop");
	return (0);
}
