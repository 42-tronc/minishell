/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/06/09 15:38:20 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#pragma GCC diagnostic ignored "-Wunused-function"

/*
EXPORT

- sort var by alpha
- prefix with 'declare -x '

export LOL _ww
	'LOL'
	'_ww'
export LOL="ww"	_ww="sadge"
	'LOL="ww"'
	'_ww="sadge"'
export LOL==poopi
	LOL="=poopi"
*/

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
	(void) input;
	(void) block;

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

/* static void	export_var(t_data *data, t_token *input)
{
	char	*var;
	char	*value;
	char	*content;
	char	*equal_sign;

	while (input)
	{
		content = input->token;
		printf("DOING %s\n", content);
		equal_sign = ft_strchr(content, '=');

		// no value
		if (!equal_sign)
		{
			printf("will set `%s` to nothing\n", content);
			ft_setenv(data->env, content, NULL);
			// printf("no equal\n");
		}

		// var with value
		else
		{
			// printf("`%s`\n", content);
			var = ft_strndup(content, equal_sign - content);
			// printf("var\t= %s\n", var);
			value = ft_strdup(equal_sign + 1);
			// printf("value\t= %s\n", value);
			ft_setenv(data->env, var, value);
		}
		input = input->next;
	}
} */

void	export_var(t_data *data, t_token *input, int block)
{
	(void) block;
	(void) data;
	char	*var;
	char	*value;
	char	*content;
	char	*equal_sign;

	while (input)
	{
		content = input->token;
		// printf("DOING %s\n", content);
		equal_sign = ft_strchr(content, '=');

		// no value
		if (!equal_sign)
		{
			printf("setting `%s` to NULL\n", content);
			ft_setenv(data->env, content, NULL);
			// printf("no equal\n");
		}

		// var with value
		else
		{
			// printf("`%s`\n", content);
			var = ft_strndup(content, equal_sign - content);
			// printf("var\t= %s\n", var);
			value = ft_strdup(equal_sign + 1);
			// printf("value\t= %s\n", value);
			ft_setenv(data->env, var, value);
		}
		input = input->next;
	}

/* 	equal_sign = 0;
	var = NULL;
	value = NULL;
	while (input)
	{
		equal_sign = ft_strchr(input->token, '=');
		if (ft_strcmp(input->type, ARG) == 0)
		{
			printf(BLUE"E: %s%s%s\n", BOLD, input->token, RESET); // REMOVE
			var = ft_strndup(input->token, equal_sign - input->token);
			if (equal_sign)
			{
				value = ft_strdup(equal_sign + 1);
				printf("equal sign\n"); // REMOVE
			}
			else
				printf("no equal sign\n");
			ft_setenv(data->env, var, value);
			printf("Found %s=`%s`\n", input->token, ft_getenv(data->env, var));
			// print = 0;
			// break;
		}
		input = input->next;
	} */
}


void	ft_export(t_data *data, t_token *input, int block)
{
	int	print;
	(void) data;
	(void) block;

	print = 1;
	while(input)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			print = 0;
			break;
		}
		input = input->next;
	}
	if (print)
		create_subshell(export_print, data, input, block);
	else
		export_var(data, input, block);

}
