/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_nbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:20:06 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/17 13:07:46 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipes(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	data->pipe_count = 1;
	while (temp)
	{
		if (!ft_strcmp(temp->token_id, PIPE))
			data->pipe_count++;
		temp = temp->next;
	}
}
