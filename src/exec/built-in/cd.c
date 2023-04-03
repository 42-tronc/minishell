/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/04/03 23:33:49 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
NEED
`cd -`	to go back in time
`cd ~`	to go home

*/

void	ft_cd(char *path)
{
	// Change to home directory
	if (!path || ft_strncmp(path, "~", 1) == 0)
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
