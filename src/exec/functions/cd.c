/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:22:58 by croy              #+#    #+#             */
/*   Updated: 2023/08/02 14:00:38 by croy             ###   ########lyon.fr   */
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
 * @brief Counts the number of arguments
 *
 * @param inpu t_token struct with the input
 * @return int number of arguments
 */
static int	check_arg_count(t_token *input)
{
	int	arg_count;

	arg_count = count_arguments(input);
	if (arg_count > 1)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
	char	*path;
	char	previous[BUFSIZ];

	ft_bzero(previous, BUFSIZ);
	if (check_arg_count(input))
		return (EXIT_FAILURE);
	while (input && input->pipe_block == block && ft_strcmp(input->type,
			ARG) != 0)
		input = input->next;
	if (!getcwd(previous, BUFSIZ))
	{
		// perror(BOLD RED "cd pwd" RESET);
		printf(BOLD RED "cd:%s current directory might have been deleted, going to "
			"home directory%s\n", NO_BOLD, RESET);
		path = ft_getenv(data->env, "HOME");
		// return (EXIT_FAILURE);
	}
	else
		path = get_cd_path(data, input);
	if (!path)
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		perror(BOLD RED "cd" RESET);
		return (EXIT_FAILURE);
	}
	ft_setenv(data, &(data->env), "OLDPWD", previous);
	return (EXIT_SUCCESS);
}
