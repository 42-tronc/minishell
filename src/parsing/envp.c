/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:17:39 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/05 19:27:13 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Create a linked list out of the envp.
/// @param envp envp variable out of the main.
/// @return pointer to first element of the linked list.
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

/// @brief Get the value of a var passed in str inside envp.
/// @param envp t_list envp to get the linked list of envp.
/// @param str Variable name with the '=' included /!\.
/// @return char * from the variable passed.
char	*ft_getenv(t_list *list_env, char *str)
{
	t_list	*temp;

	temp = list_env;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->content, str, ft_strlen(str)) == 0)
			return (ft_strdup(temp->content + ft_strlen(str)));
		temp = temp->next;
	}
	return (NULL);
}

/// @brief Change or add back a variable in our linked list of envp.
/// @param list_envp Linked list of envp
/// @param var Name of the variable with '=' at the end (IMPORTANT TO ADD =)
/// @param value The value to be replace or added to the linked list
void	add_env(t_list *list_envp, char *var, char *value)
{
	t_list	*temp;

	temp = list_envp;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->content, var, ft_strlen(var)) == 0)
		{
			free(temp->content);
			temp->content = ft_strjoin(var, value);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(&list_envp, ft_lstnew(ft_strjoin(var, value)));
}
