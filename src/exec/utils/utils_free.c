/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:43:01 by croy              #+#    #+#             */
/*   Updated: 2023/08/08 14:49:39 by croy             ###   ########lyon.fr   */
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
	while (data->cmd_block[i])
	{
		free(data->cmd_block[i]->heredoc);
		data->cmd_block[i]->heredoc = NULL;
		free(data->cmd_block[i]);
		data->cmd_block[i] = NULL;
		i++;
	}
	free(data->cmd_block);
}

void	free_quit(t_data *data)
{
	if (data && data->tokens)
	{
		free_token(data->tokens);
		data->tokens = NULL;
	}
	if (data && data->cmd_block)
	{
		free_cmd_block(data);
		data->cmd_block = NULL;
	}
	if (data && data->p)
	{
		free(data->p);
		data->p = NULL;
	}
	if (data && data->env)
	{
		free_list(data->env);
		data->env = NULL;
	}
	if (data)
	{
		free(data);
		data = NULL;
	}
}

void	free_in_while(t_data *data)
{
	if (data && data->tokens)
	{
		free_token(data->tokens);
		data->tokens = NULL;
	}
	if (data && data->p)
	{
		free(data->p);
		data->p = NULL;
	}
	if (data && data->cmd_block)
	{
		free_cmd_block(data);
		data->cmd_block = NULL;
	}
}
