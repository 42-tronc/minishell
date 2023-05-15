/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:37:28 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/03 14:37:29 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *temp)
{
	int	args;

	args = 0;
	while (temp && (!ft_strcmp(temp->token_id, CMD) \
	|| !ft_strcmp(temp->token_id, ARG)))
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

	if (ft_strcmp(temp->token_id, CMD))
		return (NULL);
	array = malloc(sizeof(char *) * (count_args(temp) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (temp && (!ft_strcmp(temp->token_id, CMD) \
	|| !ft_strcmp(temp->token_id, ARG)))
	{
		array[i] = ft_strdup(temp->token);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
