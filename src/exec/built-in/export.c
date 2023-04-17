/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:26 by croy              #+#    #+#             */
/*   Updated: 2023/04/08 17:42:18 by croy             ###   ########lyon.fr   */
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
    t_list *current;
    t_list *next;
    char *tmp;

    if (env == NULL)
        return;
    current = env;
    while (current->next)
    {
        next = current->next;
        while (next)
        {
            if (strcmp(((char *)current->content), ((char *)next->content)) > 0)
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


int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	t_list	*env;
	env = list_env(envp);
	ft_setenv(env, "MY_VAR", "world");
	ft_env(env);

	return (0);
}
