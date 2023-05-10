/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:28 by croy              #+#    #+#             */
/*   Updated: 2023/05/10 08:55:09 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_INPUT_SIZE 1000

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

char	*get_heredoc(void)
{
	line =
}

int test_heredoc(void)
{
	char	*line;
	char	input[MAX_INPUT_SIZE] = {0};
	int		input_len;

	input_len = 0;
	while ((line = readline("> ")))
	{
		// Concatenate the input line onto the end of the input string
		int line_len = strlen(line);
		if (input_len + line_len + 1 > MAX_INPUT_SIZE)
		{
			printf("Input too long!\n");
			free(line);
			break;
		}
		strcat(input, line);
		strcat(input, "\n");
		input_len += line_len + 1;
		add_history(line);
		free(line);
		if (line_len == 0) {
			break;
		}
	}

	printf("You entered:\n%s", input);

	return 0;
}

void	test_files(t_data *data, t_token *input)
{
	(void) data;
	printf("test_heredoc = %d\n", test_heredoc());
	if (!input)
	{
		printf("give me a path\n");
		return;
	}
	// char *path = input->token;
	// printf("testing `%s`\n", path);

	// printf("infile = %d\n", check_infile(path));
	// printf("outfile = %d\n", check_outfile(path));
	// printf("append = %d\n", check_append(path));
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>
