/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:43:01 by croy              #+#    #+#             */
/*   Updated: 2023/06/30 09:27:36 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **env_array)
{
	size_t	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	free_cmd_block(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_ct)
	{
		free(data->cmd_block[i]);
		i++;
	}
	free(data->cmd_block);
}

void	free_quit(t_data *data)
{
	free_token(data->tokens);
	free_cmd_block(data);
	free(data->p);
	free_list(data->env);
	free(data);
	exit(EXIT_FAILURE);
}
