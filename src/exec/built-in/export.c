/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/04/24 13:30:49 by croy             ###   ########lyon.fr   */
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

/* void ft_sort_env(t_env *env)
{
	t_env	*current;
	t_env	*next;
	char	*tmp;

	if (!env)
		return;
	current = env;
	while (current->next)
	{
		next = current->next;
		while (next)
		{
			if (strcmp(current->var, next->var) > 0)
			{
				tmp = current->var;
				current->var = next->var;
				next->var = tmp;
			}
			next = next->next;
		}
		current = current->next;
	}
} */

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


/* void	ft_setexport(t_list	*export, char *str)
{
	// check if `=` or not
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			ft_setenv(export, )
		}
		i++;
	}

} */

void	ft_export(t_env *env, char *var, char *value)
{
	// OPERATIONS GO HERE BEFORE SORTING
	// si export plusieurs mots


	printf("\n\n\n\n\tEXPORT HERE\n\n");
	ft_sort_env(env);
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->var, env->value);
		// printf("declare -x %s=\"%s\"\n", (char *)env->var, var->value);
		env = env->next;
	}
}

/* int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	t_list	*env;
	// t_list	*export;

	env = list_env(envp);
	// export = list_env(envp);
	ft_setenv(env, "MY_VAR", "world");
	// printf("\n\n\n\tOG\n\n");
	// ft_env(env);
	// ft_export(export);
	// printf("\n\n\n\tOG AGAIN\n\n");
	// ft_env(env);

	return (0);
}
 */
