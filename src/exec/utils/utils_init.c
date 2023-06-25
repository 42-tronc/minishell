/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:57:10 by croy              #+#    #+#             */
/*   Updated: 2023/06/25 14:20:37 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_default_env(t_data *data)
{
	ft_setenv(&(data->env), "OLDPWD", "");
	if (!ft_getenv(data->env, "SHLVL"))
		ft_setenv(&(data->env), "SHLVL", "1");
	else
		ft_setenv(&(data->env), "SHLVL", ft_itoa(ft_atoi(ft_getenv(data->env, "SHLVL")) + 1));
	ft_setenv(&(data->env), "PWD", getcwd(NULL, 0));
}

/**
 * @brief gets the envp from a main function and fills a t_env linked list
 * will set the variable in `var` and value in `value`
 *
 * @param envp from a main function where (char **envp)
 * @return t_env* the linked list with every var and its value from the env
 */
void	fill_env(t_data *data, char **envp)
{
	int		i;
	int		j;
	t_env	*current;

	i = 0;
	data->env = NULL;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				envp[i][j] = '\0';
				current = ft_env_new(envp[i], envp[i] + j + 1);
				if (!current)
					exit_error(E_MALLOC, "fill_env");
				ft_env_add_back(&(data->env), current);
				break ;
			}
			j++;
		}
		i++;
	}
	fill_default_env(data);
}
