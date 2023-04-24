/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/04/24 18:40:21 by croy             ###   ########lyon.fr   */
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

void	ft_sort_env(t_env *env)
{
	t_env	*current;
	t_env	*next;
	t_env	*tmp;

	if (!env)
		return ;
	current = env;
	while (current->next)
	{
		next = current->next;
		while (next)
		{
			if (strcmp(current->var, next->var) > 0)
			{
				tmp = current->next;
				current->next = next->next;
				next->next = tmp;
				tmp = current;
				current = next;
				next = tmp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

void args_to_export(t_env *env, t_list *args)
{
	char *var;
	char *value;
	char *content;
	char *equal_sign;

    while (args)
    {
		content = args->content;
		printf("DOING %s\n", content);
		equal_sign = strchr(content, '=');

		// no value
        if (!equal_sign)
		{
			printf("will set `%s` to nothing\n", content);
			ft_setenv(env, content, "");
			printf("no equal\n");
		}

		// var with value
        else
        {
			// printf("`%s`\n", content);
            var = ft_strndup(content, equal_sign - content);
			// printf("var\t= %s\n", var);
            value = ft_strdup(equal_sign + 1);
			// printf("value\t= %s\n", value);
            ft_setenv(env, var, value);
        }
        args = args->next;
    }
}

void	ft_export(t_env *env, t_list *args)
{
	// OPERATIONS GO HERE BEFORE SORTING
	// si export plusieurs mots

	ft_setenv(env, "GTK_MODULES", "lol");
	ft_setenv(env, "NOT_GTK_MODULES", "prev");
	ft_setenv(env, "NOT_GTK_MODULES", "");
	ft_setenv(env, "yep", "");

	// int i = 0;
	// char *content;
	// char *var;
	// char *value;

	args_to_export(env, args);
	/* while (args)
	{
		content = args->content;
		printf("%s\n", content);

		while (content[i])
		{
			// printf("i=%d\n", i);
			if (content[i] == '=')
			{
				content[i] = '\0';
				var = ft_strdup(content);
				// printf("var=`%s`\n", var);
				content += i + 1;
				value = ft_strdup(content);
				// printf("value=`%s`\n", value);
				// printf("breaking\n");
				break;

				// ft_setenv(env, var, ft_strdup(content));
				// printf("%c here \n", content[i]);
			}
			i++;
		}
		// printf("we out bitch\n");
		printf("`%s` = ", var);
		printf("`%s`\n", value);
		ft_setenv(env, var, value);
		args = args->next;
	} */

	printf("\n\n\n\n\tEXPORT HERE\n\n");
	ft_sort_env(env);
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->var, env->value);
		env = env->next;
	}
}
