/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:17:39 by arthurasced       #+#    #+#             */
/*   Updated: 2023/06/29 09:28:09 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Free a given list.
/// @param lst The list to be free'd.
void	free_list(t_env *lst)
{
	t_env	*current;
	t_env	*temp1;

	if (!lst)
		return ;
	current = lst;
	while (current != NULL)
	{
		temp1 = current;
		current = current->next;
		free(temp1->var);
		free(temp1->value);
		free(temp1);
	}
}
