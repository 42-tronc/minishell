/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:17:39 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/18 16:23:01 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Free a given list.
/// @param lst The list to be free'd.
void	free_list(t_list *lst)
{
	t_list	*current;
	t_list	*temp1;

	current = lst;
	while (current != NULL)
	{
		temp1 = current;
		current = current->next;
		free(temp1->content);
		free(temp1);
	}
}

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
		printf("adding: `%s`\n", envp[i]);
		/*
		2 strdup si y'a un `=`
			si GDK_BACKEND=x11
			go jusqua `=`
			remplacer par un `\0` le `=`
			strdup premier mot
			++ pour skip lespace
			strdup le deuxieme mot
		sinon 1 strdup du premier mot
		 */
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
			return (ft_strdup(temp->content + ft_strlen(str) + 1));
		temp = temp->next;
	}
	return (NULL);
}

/// @brief Change or add back a variable in our linked list of envp.
/// @param list_envp Linked list of envp
/// @param var Name of the variable with '=' at the end (IMPORTANT TO ADD =)
/// @param value The value to be replace or added to the linked list
int	ft_setenv(t_list *list_envp, char *var, char *value)
{
	t_list	*temp;
	char	*var_prefixed;

	temp = list_envp;
	// Add `=` to var
	var_prefixed = malloc((ft_strlen(var) + 2) * sizeof(char));
	if (!var_prefixed)
		return (-1); // to change if malloc fails
	ft_strlcpy(var_prefixed, var, ft_strlen(var) + 2);
	ft_strlcat(var_prefixed, "=", ft_strlen(var) + 2);
	// printf("old var: `%s`\nnew var: `%s`\n", var, var_prefixed);

	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->content, var, ft_strlen(var)) == 0)
		{
			free(temp->content);
			temp->content = ft_strjoin(var_prefixed, value);
			free(var_prefixed);
			return (0);
		}
		temp = temp->next;
	}
	ft_lstadd_back(&list_envp, ft_lstnew(ft_strjoin(var_prefixed, value)));
	free(var_prefixed);
	return (0);
}

/*
/// @brief Change or add back a variable in our linked list of envp.
/// @param list_envp Linked list of envp
/// @param var Name of the variable with '=' at the end (IMPORTANT TO ADD =)
/// @param value The value to be replace or added to the linked list
void	ft_setenv(t_list *list_envp, char *var, char *value)
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
} */
