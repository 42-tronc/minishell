/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:00:46 by croy              #+#    #+#             */
/*   Updated: 2023/04/27 10:09:26 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
Use: getcwd

	PATH_MAX (defined in limits.h)
	FILENAME_MAX (defined in stdio.h)
both of these are set to 4096 on my system (x86 Linux).
*/

int	ft_pwd(void)
{
	char	cwd[BUFSIZ];

	if (getcwd(cwd, BUFSIZ))
		printf("PWD='%s'\n", cwd);
	else
		return (perror("pwd"), 1);
	return (0);
}
