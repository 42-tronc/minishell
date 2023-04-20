/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:25:08 by croy              #+#    #+#             */
/*   Updated: 2023/04/20 11:45:35 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODO

unset a var and remove it from the export list
 */

void	ft_unset()
{

}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	t_env	*env;
	env = list_env(envp);
	ft_setenv(env, "MY_VAR", "world");
	ft_env(env);
	printf("\n\n\n\nSORTED HERE\n\n");
	ft_sort_env(env);
	ft_env(env);

	return (0);
}
