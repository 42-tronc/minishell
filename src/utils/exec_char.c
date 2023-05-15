/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:37:28 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/15 15:38:31 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *temp)
{
	int	args;

	args = 0;
	while (temp && (!ft_strcmp(temp->type, CMD) \
	|| !ft_strcmp(temp->type, ARG)))
	{
		args++;
		temp = temp->next;
	}
	return (args);
}

char	**get_array_cmd(t_token *temp)
{
	char	**array;
	int		i;

	if (ft_strcmp(temp->type, CMD))
		return (NULL);
	array = malloc(sizeof(char *) * (count_args(temp) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (temp && (!ft_strcmp(temp->type, CMD) \
	|| !ft_strcmp(temp->type, ARG)))
	{
		array[i] = ft_strdup(temp->token);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
