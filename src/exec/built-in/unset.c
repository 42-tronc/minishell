/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:25:08 by croy              #+#    #+#             */
/*   Updated: 2023/06/19 15:10:29 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *node)
{
	free(node->var);
	free(node->value);
	free(node);
}

static void	unset_key(t_env **env, const char *token)
{
	t_env	*tmp;
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->var, token) == 0)
		{
			printf("found %s\n", token);
			if (!previous)
				*env = current->next;
			else
				previous->next = current->next;
			tmp = current;
			current = current->next;
			free_env(tmp);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_env **env, t_token *input, int block)
{
	while (input && input->pipe_block == block)
	{
		unset_key(env, input->token);
		input = input->next;
	}
}
