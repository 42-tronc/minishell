/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:23:26 by croy              #+#    #+#             */
/*   Updated: 2023/07/25 16:10:40 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief prints the environment variables
 *
 * @param data t_data struct with env
 * @param input t_token struct to check if there are any args
 * @param block to check for args in the current block
 * @return int EXIT_SUCCESS or EXIT_FAILURE
 */
int	print_env(t_data *data, t_token *input, int block)
{
	t_env	*save;

	save = data->env;
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			write(STDERR_FILENO, "\e[31menv doesn't take any arguments\n", 35);
			return (EXIT_FAILURE);
		}
		input = input->next;
	}
	while (data->env)
	{
		if (data->env->value)
			printf("%s=%s\n", data->env->var, data->env->value);
		data->env = data->env->next;
	}
	data->env = save;
	return (0);
}
