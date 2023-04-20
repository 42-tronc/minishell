/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:38:39 by croy              #+#    #+#             */
/*   Updated: 2023/04/20 13:25:14 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
NEED

	Fill env to linked list
	Get value from var in linked list
	Set value from var in linked list
 */

void	fill_env(char **envp)
{
	int		i;
	t_env	*env;

	while (envp[i])
		printf(envp[i++]);
}

int main(int argc, char *argv[], char **envp)
{
	(void) argc;
	(void) argv;
	fill_env(envp);
	return 0;
}
