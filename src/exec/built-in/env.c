/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:23:26 by croy              #+#    #+#             */
/*   Updated: 2023/04/06 18:06:01 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env)
{
	t_list	*current;

	current = env;
	while (current)
	{
		printf("data: %s, next: %p\n", (char *)current->content, current->next);
		current = current->next;
	}
}

int	main(void, void, char **envp)
{
	// t_list	*list = malloc(sizeof(t_list));

	// list->content = 1;
	// list->next = malloc(sizeof(t_list));
	// list->next->content = 2;
	// list->next->next = NULL;

	t_list	*env;

	env = list_env(envp);
	print_env(env);
	return 0;
}
