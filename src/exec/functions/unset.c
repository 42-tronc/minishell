/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:25:08 by croy              #+#    #+#             */
/*   Updated: 2023/08/04 15:21:17 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env *node)
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
			if (!previous)
				*env = current->next;
			else
				previous->next = current->next;
			tmp = current;
			current = current->next;
			free_env_node(tmp);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(t_data *data, t_token *input, int block)
{
	int		status;
	t_env	**env;

	status = EXIT_SUCCESS;
	env = &data->env;
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			if (!check_var_name(input->token, "unset"))
				unset_key(env, input->token);
			else
				status = EXIT_FAILURE;
		}
		input = input->next;
	}
	return (status);
}
