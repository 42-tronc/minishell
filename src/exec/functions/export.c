/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/08/04 15:16:24 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_sort(t_env *env)
{
	t_env	*current;
	t_env	*next;

	if (!env)
		return ;
	current = env;
	while (current->next)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(current->var, next->var) > 0)
			{
				swap_var(&current->var, &next->var);
				swap_var(&current->value, &next->value);
			}
			next = next->next;
		}
		current = current->next;
	}
}

int	check_var_name(char *var, char *fn)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	if (!var || !var[0])
		status = 1;
	while (var && var[++i])
	{
		if (!ft_isalpha(var[0]) && var[0] != '_')
			status = 1;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			status = 1;
	}
	if (status)
	{
		write(2, fn, ft_strlen(fn));
		write(2, ": ", 2);
		write(2, var, ft_strlen(var));
		ft_putendl_fd(": not a valid identifier", 2);
	}
	return (status);
}

int	add_env_entry(t_data *data, t_token *input, int block)
{
	char	*var;
	char	*value;

	if (!input)
		return (1);
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			var = ft_strdup(input->token);
			if (!var)
				exit_error(data, E_MALLOC, "add_env_entry");
			value = ft_strchr(var, '=');
			if (value)
				*value = '\0';
			if (value)
				value++;
			if (check_var_name(var, "export"))
				return (free(var), 1);
			ft_setenv(data, &(data->env), var, value);
			free(var);
		}
		input = input->next;
	}
	return (0);
}

static int	export_print(t_data *data, t_token *input, int block)
{
	t_env	*save;

	save = data->env;
	(void)input;
	(void)block;
	if (!data->env)
		return (1);
	export_sort(data->env);
	while (data->env)
	{
		if (data->env->value)
			printf("declare -x %s=\"%s\"\n", data->env->var, data->env->value);
		else
			printf("declare -x %s\n", data->env->var);
		data->env = data->env->next;
	}
	data->env = save;
	return (0);
}

int	ft_export(t_data *data, t_token *input, int block)
{
	int	status;

	status = 0;
	if (count_arguments(input) == 0)
		create_subshell(export_print, data, input, block);
	else
		status = check_alone(add_env_entry, data, input, block);
	return (status);
}
