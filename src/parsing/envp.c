/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:17:39 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/04 13:44:06 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_envp(char **envp)
{
	int		i;
	t_list	*list_envp;

	list_envp = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&list_envp, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (list_envp);
}