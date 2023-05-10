/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:28 by croy              #+#    #+#             */
/*   Updated: 2023/05/10 08:37:15 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	// if (fd == -1)
	// {
	// 	perror("open");
	// 	return (FAILURE);
	// }
	return (fd);
}

int	check_outfile(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		perror("open");
		return (FAILURE);
	}
	return (fd);
}

int	check_append(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
	{
		perror("open");
		return (FAILURE);
	}
	return (fd);
}

void	test_files(t_data *data, t_token *input)
{
	(void) data;
	if (!input)
	{
		printf("give me a path\n");
		return;
	}
	char *path = input->token;
	printf("testing `%s`\n", path);

	printf("infile = %d\n", check_infile(path));
	printf("outfile = %d\n", check_outfile(path));
	printf("append = %d\n", check_append(path));
}
