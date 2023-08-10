/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:32:17 by croy              #+#    #+#             */
/*   Updated: 2023/08/10 12:32:47 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*execve_nopath(t_data *data, t_token *input,
		char **env_array, char *command_path)
{
	command_path = ft_strdup(input->token);
	if (!command_path)
	{
		free_array(env_array);
		clean_exit(data, E_MALLOC, "execve_nopath");
	}
	return (command_path);
}
