/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:23:26 by croy              #+#    #+#             */
/*   Updated: 2023/06/09 11:09:18 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data *data, t_token *input, int block)
{
	(void)input;
	(void)block;
	while (data->env)
	{
		printf("%s=%s\n", data->env->var, data->env->value);
		data->env = data->env->next;
	}
}

void	ft_env(t_data *data, t_token *input, int block)
{
	create_subshell(print_env, data, input, block);
}
