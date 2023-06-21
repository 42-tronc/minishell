/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:43:01 by croy              #+#    #+#             */
/*   Updated: 2023/06/21 11:43:08 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **env_array)
{
	char	**current;

	if (!env_array)
		return ;
	current = env_array;
	while (*current)
	{
		free(*current);
		current++;
	}
	free(env_array);
}
