/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/04/04 14:11:17 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
NEED
`cd -`	to go back in time
`cd ~`	to go home
`cd ~~`	to go home

*/

void	ft_cd(char *path)
{
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

int	main(int ac, char **av)
{
	printf("getenv HOME='%s'\n", getenv("HOME"));
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
