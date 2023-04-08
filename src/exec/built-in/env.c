/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:23:26 by croy              #+#    #+#             */
/*   Updated: 2023/04/08 17:08:28 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list *env)
{
	t_list	*current;

	current = env;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		// printf("data: %s, next: %p\n", (char *)current->content, current->next);
		current = current->next;
	}
}

/* int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	t_list	*env;
	env = list_env(envp);
	ft_env(env);

	return (0);
} */
