/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:22:45 by croy              #+#    #+#             */
/*   Updated: 2023/08/11 15:22:53 by croy             ###   ########lyon.fr   */
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
t_env	*ft_env_new(t_data *data, char *var, char *value)
{
	t_env	*dst;

	dst = malloc(sizeof(t_env));
	if (!dst)
		clean_exit(data, E_MALLOC, "ft_env_new");
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
		clean_exit(data, E_MALLOC, "ft_env_new");
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
