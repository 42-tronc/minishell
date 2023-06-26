/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:57:10 by croy              #+#    #+#             */
/*   Updated: 2023/06/26 12:49:00 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_default_env(t_data *data)
{
	char	*shlvl;
	char	*cwd;

	ft_setenv(&(data->env), "OLDPWD", NULL);
	if (!ft_getenv(data->env, "SHLVL"))
		ft_setenv(&(data->env), "SHLVL", "1");
	else if (ft_atoi(ft_getenv(data->env, "SHLVL")) >= 999)
	{
		write(2, "bash: warning: shell level too high, resetting to 1\n", 52);
		ft_setenv(&(data->env), "SHLVL", "1");
	}
	else
	{
		shlvl = ft_itoa(ft_atoi(ft_getenv(data->env, "SHLVL")) + 1);
		ft_setenv(&(data->env), "SHLVL", shlvl);
		free(shlvl);
	}
	if (!ft_getenv(data->env, "PWD"))
	{
		cwd = getcwd(NULL, 0);
		ft_setenv(&(data->env), "PWD", cwd);
		free(cwd);
	}
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
