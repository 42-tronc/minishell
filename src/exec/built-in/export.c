/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/06/09 20:33:02 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_var(char **current, char **next)
{
	char	*tmp;

	tmp = *current;
	*current = *next;
	*next = tmp;
}

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

static void	export_print(t_data *data, t_token *input, int block)
{
	(void)input;
	(void)block;
	if (!data->env)
		return ;
	export_sort(data->env);
	while (data->env)
	{
		if (data->env->value)
			printf("declare -x %s=\"%s\"\n", data->env->var, data->env->value);
		else
			printf("declare -x %s\n", data->env->var);
		data->env = data->env->next;
	}
}

void	add_env_entry(t_env *env, t_token *input, int block)
{
	char	*var;
	char	*value;

	if (!input)
		return ;
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			var = strdup(input->token);
			value = strchr(var, '=');
			if (value)
			{
				*value = '\0';
				value++;
			}
			// else
			printf("var = `%s` | value = `%s`\n", var, value);
			ft_setenv(env, var, value);
			printf("getenv %s = `%s`\n", var, ft_getenv(env, var));
		}
		input = input->next;
	}

}

void	ft_export(t_data *data, t_token *input, int block)
{
	int	print;

	(void)data;
	(void)block;
	print = 1;
	while (input)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			print = 0;
			break ;
		}
		input = input->next;
	}
	if (print)
		create_subshell(export_print, data, input, block);
	else
		add_env_entry(data->env, input, block);
}
