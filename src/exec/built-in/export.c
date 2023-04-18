/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/04/18 15:36:43 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
EXPORT

- sort var by alpha
- prefix with 'declare -x '

export LOL _ww
	will add 'LOL' AND '_ww' in export
export LOL="ww"	_ww="sadge"
	will add and set 'LOL="ww"' AND '_ww="sadge"' in export


 */

void ft_sort_env(t_list *env)
{
	t_list	*current;
	t_list	*next;
	char	*tmp;

	if (!env)
		return;
	current = env;
	while (current->next)
	{
		next = current->next;
		while (next)
		{
			if (strcmp(current->content, next->content) > 0)
			{
				tmp = current->content;
				current->content = next->content;
				next->content = tmp;
			}
			next = next->next;
		}
		current = current->next;
	}
}



void	ft_export(t_list *env)
{
	printf("\n\n\n\n\tEXPORT HERE\n\n");
	ft_sort_env(env);
	while (env)
	{
		printf("declare -x %s\n", (char *)env->content);
		// printf("declare -x %s=\"%s\"\n", (char *)env->var, var->value);
		env = env->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	t_list	*env;
	// t_list	*export;

	env = list_env(envp);
	// export = list_env(envp);
	ft_setenv(env, "MY_VAR", "world");
	printf("\n\n\n\tOG\n\n");
	ft_env(env);
	// ft_export(export);
	// printf("\n\n\n\tOG AGAIN\n\n");
	// ft_env(env);

	return (0);
}
