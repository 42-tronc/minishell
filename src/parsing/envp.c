/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:17:39 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/05 11:49:36 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*list_env(char **envp)
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

char	*ft_getenv(char **envp, char *str)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0
			&& envp[i][ft_strlen(str)] == '=')
			return (ft_strdup(envp[i] + ft_strlen(str) + 1));
	}
	return (NULL);
}
