/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/06/07 14:42:40 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_sort_env(t_env *env)
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

/**
 * @brief takes the args and export those in the t_env
 *
 * @param env t_env of export
 * @param args t_list of the args with args.content being each token
 */
static void	args_to_export(t_data *data, t_token *input)
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
}

/*
If `export loli`
	`loli`
if `export lol=`
	`lol=""`
*/

// void	ft_export(t_env *env, t_list *args)
void	ft_export(t_data *data, t_token *input)
{
	// ft_setenv(env, "GTK_MODULES", "lol");
	// ft_setenv(env, "__NOT_GTK_MODULES", "prev");
	// ft_setenv(env, "__NOT_GTK_MODULES", "");
	// ft_setenv(env, "__yep", "");

	args_to_export(data, input);
	getenv(input->token);

	// printf("\n\n\n\n\tEXPORT HERE\n\n");
	ft_sort_env(data->env);
	// while (data->env)
	// {
	// 	if (data->env->value)
	// 		printf("declare -x %s=\"%s\"\n", data->env->var, data->env->value);
	// 	else
	// 		printf("declare -x %s\n", data->env->var);
	// 	data->env = data->env->next;
	// }
}
