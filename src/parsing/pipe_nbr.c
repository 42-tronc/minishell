/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_nbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:20:06 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/15 15:33:43 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	give_pipe_nbr(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp)
	{
		if (!temp->prev)
			temp->pipe_block = 0;
		else if (ft_strcmp(temp->type, PIPE))
			temp->pipe_block = temp->prev->pipe_block;
		else
			temp->pipe_block = temp->prev->pipe_block + 1;
		temp = temp->next;
	}
}
