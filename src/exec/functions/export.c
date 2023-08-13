/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/08/13 10:30:01 by croy             ###   ########lyon.fr   */
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

static int	add_env_if_arg(t_data *data, t_token *input)
{
	int		exit_code;
	char	*var;
	char	*value;

	exit_code = EXIT_SUCCESS;
	var = ft_strdup(input->token);
	if (!var)
		clean_exit(data, E_MALLOC, "add_env_entry");
	value = ft_strchr(var, '=');
	if (value)
		*value = '\0';
	if (value)
		value++;
	if (check_var_name(var, "export"))
	{
		free(var);
		exit_code = EXIT_FAILURE;
	}
	else
		ft_setenv_mallocd(data, var, value, var);
	return (exit_code);
}

int	add_env_entry(t_data *data, t_token *input, int block)
{
	int	exit_code;

	exit_code = 0;
	if (!input)
		return (1);
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			if (add_env_if_arg(data, input))
				exit_code = 1;
		}
		input = input->next;
	}
	return (exit_code);
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
