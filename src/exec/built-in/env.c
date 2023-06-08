/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:23:26 by croy              #+#    #+#             */
/*   Updated: 2023/06/08 12:48:39 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data *data, t_token *input, int block)
{
	(void) input;
	(void) block;
	t_env	*current;

	current = data->env;
	while (current)
	{
		printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
}

void	ft_env(t_data *data, t_token *input, int block)
{
	create_subshell(print_env, data, input, block);
}

/* void	ft_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
} */
