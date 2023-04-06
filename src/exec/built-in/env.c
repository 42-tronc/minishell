/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:23:26 by croy              #+#    #+#             */
/*   Updated: 2023/04/06 17:32:10 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env)
{
	t_list	*current;

	current = env;
	while (current)
	{
		printf("data: %d, next: %p\n", current->content, current->next);
		current = current->next;
	}
}

/* int	main(void)
{
	t_list	*list = malloc(sizeof(t_list));

	list->content = 1;
	list->next = malloc(sizeof(t_list));
	list->next->content = 2;
	list->next->next = NULL;

	// Print the contents of the linked list
	print_env(list);

	return 0;
} */
