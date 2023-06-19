/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/06/19 13:30:41 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @brief Counts the number of arguments in the input
 *
 * @param input input with the first argument
 * @param block block of the pipe
 * @return int number of arguments
 */
static int	count_arguments(t_token *input, int block)
{
	int		arg_count;
	t_token	*current;

	arg_count = 0;
	current = input;
	while (current && current->pipe_block == block)
	{
		if (ft_strcmp(current->type, ARG) == 0)
			arg_count++;
		current = current->next;
	}
	return (arg_count);
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

	arg_count = count_arguments(input, block);
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
		return (1);
	if (chdir(path) == -1)
		perror("cd");
	else
		ft_setenv(data->env, "OLDPWD", previous);
	return (0);
}
