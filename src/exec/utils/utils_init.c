/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:57:10 by croy              #+#    #+#             */
/*   Updated: 2023/08/14 10:09:15 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_default_env(t_data *data)
{
	char	*cwd;
	char	*shlvl;

	data->need_free = 0;
	if (!ft_getenv(data->env, "SHLVL"))
		ft_setenv(data, &(data->env), "SHLVL", "1");
	else if (ft_atoi(ft_getenv(data->env, "SHLVL")) >= 999)
	{
		write(2, "bash: warning: shell level too high, resetting to 1\n", 52);
		ft_setenv(data, &(data->env), "SHLVL", "1");
	}
	else
	{
		shlvl = ft_itoa(ft_atoi(ft_getenv(data->env, "SHLVL")) + 1);
		if (!shlvl)
			clean_exit(data, E_MALLOC, "fill_default_env");
		ft_setenv_mallocd(data, "SHLVL", shlvl, shlvl);
	}
	if (!ft_getenv(data->env, "PWD"))
	{
		cwd = getcwd(NULL, 0);
		ft_setenv_mallocd(data, "PWD", cwd, cwd);
	}
	ft_setenv(data, &(data->env), "OLDPWD", NULL);
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
				current = ft_env_new(data, envp[i], envp[i] + j + 1);
				if (!current)
					clean_exit(data, E_MALLOC, "fill_env");
				ft_env_add_back(&(data->env), current);
				break ;
			}
			j++;
		}
		i++;
	}
	fill_default_env(data);
}

void	count_cmd_ct(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	data->cmd_ct = 1;
	while (temp)
	{
		if (!ft_strcmp(temp->type, PIPE))
			data->cmd_ct++;
		temp = temp->next;
	}
}

int	init_data(t_data *data)
{
	int		i;

	count_cmd_ct(data);
	data->cmd_block = ft_calloc(data->cmd_ct + 1, sizeof(t_cmd_block *));
	if (!data->cmd_block)
		print_error(E_MALLOC, "init_data");
	if (!data->cmd_block)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->cmd_ct)
	{
		data->cmd_block[i] = ft_calloc(1, sizeof(t_cmd_block));
		if (!data->cmd_block[i])
		{
			print_error(E_MALLOC, "init_data");
			free_cmd_block(data);
			return (EXIT_FAILURE);
		}
		data->cmd_block[i]->in_fd = -2;
		data->cmd_block[i]->out_fd = -2;
		data->cmd_block[i]->pipe_fd[0] = -2;
		data->cmd_block[i]->pipe_fd[1] = -2;
		data->cmd_block[i++]->heredoc_here = 0;
	}
	return (EXIT_SUCCESS);
}
