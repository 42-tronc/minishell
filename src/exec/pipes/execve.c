/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/05/04 15:26:39 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getpaths(t_data *data)
{
	char *paths;

	paths = ft_getenv(data->env, "PATH");
	data->paths = ft_split(paths, ':');
	// printf("`%s`\n", paths);
	// int i = 0;
	// while (data->paths[i])
	// {
	// 	printf("path[%d]=`%s`\n", i, data->paths[i]);
	// 	i++;
	// }
}
