/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/06/19 17:05:57 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the path to change directory to
 *
 * @param data t_data struct with every var in it
 * @param input t_token struct with the input
 * @return char* path to change directory to
 */
static char	*get_cd_path(t_data *data, t_token *input)
{
	char	*path;

	if (!input || ft_strcmp(input->token, "~") == 0)
		path = ft_getenv(data->env, "HOME");
	else if (ft_strcmp(input->token, "-") == 0)
	{
		if (ft_getenv(data->env, "OLDPWD"))
		{
			path = ft_getenv(data->env, "OLDPWD");
			printf("%s\n", path);
		}
		else
		{
			printf("cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		path = input->token;
	return (path);
}

/**
 * @brief Changes the current working directory
 * `cd` or `cd ~` will go to the home directory
 * `-` will go to the last directory if available.
 *
 * @param data t_data struct
 * @param input t_token from the first argument
 * @param block block of the pipe
 * @return int 0 if success, 1 if failure
 */
int	ft_cd(t_data *data, t_token *input, int block)
{
	int		arg_count;
	char	*path;
	char	previous[BUFSIZ];

	arg_count = count_arguments(input);
	if (arg_count > 1)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	while (input && input->pipe_block == block && ft_strcmp(input->type,
			ARG) != 0)
		input = input->next;
	getcwd(previous, BUFSIZ);
	path = get_cd_path(data, input);
	if (!path)
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	else
		ft_setenv(data->env, "OLDPWD", previous);
	return (EXIT_SUCCESS);
}
