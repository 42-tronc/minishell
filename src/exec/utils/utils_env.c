/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:19:50 by croy              #+#    #+#             */
/*   Updated: 2023/08/11 15:43:38 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	ft_addenv(t_data *data, t_env **env, char *var, char *value)
{
	t_env	*new_entry;

	if (!var)
		return (1);
	new_entry = ft_env_new(data, var, value);
	if (!new_entry)
		return (2);
	if (*env)
		ft_env_add_back(env, new_entry);
	else
		*env = new_entry;
	return (0);
}

void	ft_setenv_mallocd(t_data *data, char *var, char *value, char *malc)
{
	int	status;

	data->need_free = 1;
	status = ft_setenv(data, &(data->env), var, value);
	free(malc);
	data->need_free = 0;
	if (status == -1)
		clean_exit(data, E_MALLOC, "ft_setenv 2727");
}

int	ft_setenv(t_data *data, t_env **env, char *var, char *value)
{
	t_env	*current;

	current = *env;
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
			{
				if (data->need_free)
					return (-1);
				clean_exit(data, E_MALLOC, "ft_setenv 1");
			}
			return (0);
		}
		current = current->next;
	}
	return (ft_addenv(data, env, var, value));
}
