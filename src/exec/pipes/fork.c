/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:49:52 by croy              #+#    #+#             */
/*   Updated: 2023/06/12 16:25:15 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	ft_fork(void)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0) // Error
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) // Child process
	{
		printf("Child process\n");
		exit(EXIT_SUCCESS); // close child
	}
	else // Parent process
	{
		printf("Parent process\n");
		wait(&status); // Wait for child to close
		if (WIFEXITED(status))
			printf("Child process terminated with status %d\n",
				WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("Child process terminated by signal %d\n", WTERMSIG(status));
	}
	// waitpid
}
