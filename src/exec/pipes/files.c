/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:28 by croy              #+#    #+#             */
/*   Updated: 2023/05/11 14:47:58 by croy             ###   ########lyon.fr   */
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
		// perror("open");
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

/* TO CHECK
[maplepy@winter minishell]$ << test << bjr cat
> bjr
> bjr
> bjr
> bjr
> test
> test
> test
> bjr
test
test

[maplepy@winter minishell]$ << test << lol cat
te
> lol
> lol
> lol
> cat
> test
> lol
*/

void	get_heredoc(char *separator)
{
	char	*line;
	char	*document;

	document = NULL;
	printf("in the `%s` heredoc\n", separator);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", separator);
			break;
		}
		if (ft_strcmp(line, separator) == 0)
		{
			printf("found the EOF\n");
			// free(line); // ?? is it needed?
			break;
		}
		document = ft_strjoin_heredoc(document, line);
	}
	printf("document=\n%s%s"RESET, RED, document);
}

void	test_files(t_data *data, t_token *input)
{
	(void) data;
	(void) input;
	// printf("test_heredoc = %d\n", test_heredoc());
	// printf("get_heredoc = %s\n", get_heredoc());
	get_heredoc("EOF");
	get_heredoc("test");
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
