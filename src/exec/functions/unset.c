/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:25:08 by croy              #+#    #+#             */
/*   Updated: 2023/08/13 10:16:10 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env *node)
{
	free(node->var);
	free(node->value);
	free(node);
}

int	check_var_name(char *var, char *fn)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	if (!var || !var[0])
		status = 1;
	while (var && var[++i])
	{
		if (!ft_isalpha(var[0]) && var[0] != '_')
			status = 1;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			status = 1;
	}
	if (status)
	{
		write(2, fn, ft_strlen(fn));
		write(2, ": ", 2);
		write(2, var, ft_strlen(var));
		ft_putendl_fd(": not a valid identifier", 2);
	}
	return (status);
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
