/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:19:50 by croy              #+#    #+#             */
/*   Updated: 2023/06/21 09:55:13 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new t_env entry with the given variable and value.
 *
 * @param var The variable string.
 * @param value The value string.
 * @return t_env* A pointer to the newly created t_env entry.
 * @note The returned pointer should be freed when no longer needed.
 * @note If the allocation fails, the function exits with an error.
 */
t_env	*ft_env_new(char *var, char *value)
{
	t_env	*dst;

	dst = malloc(sizeof(t_env));
	if (!dst)
		exit_error(E_MALLOC, "ft_env_new");
	dst->var = NULL;
	dst->value = NULL;
	if (var)
		dst->var = ft_strdup(var);
	if (dst->var && value)
		dst->value = ft_strdup(value);
	if (!dst->var || (value && !dst->value))
	{
		if (!dst->value)
			free(dst->var);
		free(dst);
		exit_error(E_MALLOC, "ft_env_new");
	}
	dst->next = NULL;
	return (dst);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

char	*ft_getenv(t_env *env, char *var)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->var, var) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

static int	ft_addenv(t_env **env, char *var, char *value)
{
	t_env	*new_entry;

	if (!var)
		return (1);
	new_entry = ft_env_new(var, value);
	if (!new_entry)
		return (2);
	ft_env_add_back(env, new_entry);
	return (0);
}

int	ft_setenv(t_env *env, char *var, char *value)
{
	t_env	*current;

	current = env;
	if (!var)
		return (1);
	while (current)
	{
		if (ft_strcmp(current->var, var) == 0)
		{
			if (!value)
				return (0);
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	return (ft_addenv(&env, var, value));
}
