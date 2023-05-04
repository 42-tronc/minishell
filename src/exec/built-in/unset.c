/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:25:08 by croy              #+#    #+#             */
/*   Updated: 2023/05/03 14:53:55 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
NEED TO

3 cas differents:
- debut
	null les vars
	free
	reset le head de la liste a la 2eme liste
- milieu
	set le next du previous sur `current->next`
	null les vars
	free
- fin
	set le next du previous sur `NULL`
	null les vars
	free

*/

void	free_env(t_env *node)
{
	free(node->var);
	free(node->value);
	free(node);
}

void	ft_unset(t_env **env, t_token *args)
{
	t_env	*current;
	t_env	*tmp;
	t_env	*prev;

	while (args)
	{
		current = *env;
		prev = NULL;
		while (current)
		{
			// found node to delete
			if (ft_strcmp(args->token, current->var) == 0)
			{
				printf("found %s\n", args->token);
				// is the first node
				if (!prev)
					*env = current->next;
				// not the first node
				else
					prev->next = current->next;
				tmp = current;
				current = current->next;

				free_env(tmp);
				// free(tmp->var);
				// free(tmp->value);
				// free(tmp);
				break;
			}
			prev = current;
			current = current->next;
		}
		args = args->next;
	}
}

/* int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

// 	t_env	*env;
// 	env = list_env(envp);
// 	ft_setenv(env, "MY_VAR", "world");
// 	ft_env(env);
// 	printf("\n\n\n\nSORTED HERE\n\n");
// 	ft_sort_env(env);
// 	ft_env(env);

	return (0);
} */
