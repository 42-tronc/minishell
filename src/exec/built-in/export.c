/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/04/17 14:03:19 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
EXPORT

- sort var by alpha
- prefix with 'declare -x '

could do with an index,
 */

void ft_sort_env(t_list *env)
{
	t_list	*current;
	t_list	*next;
	char	*tmp;

	if (env == NULL)
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
	while (env)
	{
		printf("declare -x %s\n", (char *)env->content);
		env = env->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	t_list	*env;
	env = list_env(envp);
	ft_setenv(env, "MY_VAR", "world");
	ft_env(env);
	ft_export(env);
	printf("\n\n\nCIAO BELLI BELLA\n\n\n\n");
	ft_env(env);

	return (0);
}
