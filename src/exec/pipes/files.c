/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:28 by croy              #+#    #+#             */
/*   Updated: 2023/05/23 11:34:52 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #define MAX_INPUT_SIZE 1000

// int	check_infile(char *path)
// {
// 	int	fd;

// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return (FAILURE);
// 	}
// 	return (fd);
// }

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

	int	fd[2];
	int	pid = 0;

	if (pipe(fd) == -1)
	{
        perror("pipe");
        exit(EXIT_FAILURE);
    }
	pid = fork();
    if (pid == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }

	if (pid == 0)
	{
		// char	msg[8];
		close(fd[0]);
		write(fd[1], "madame", 7); // could check if return -1 so error
		close(fd[1]);
		// read(fd[0], &msg, sizeof(msg));
		// printf("Child\t`%s`\n", msg);
		// close(fd[0]);
		// printf("I am the child (%d)\n", pid);
	}
	else
	{
		char	msg[8];
		close(fd[1]);
		read(fd[0], &msg, sizeof(msg)); // could check if return -1 so error
		close(fd[0]);
		printf("Parent\t`%s`\n", msg);
		wait(NULL);
		// printf("I am the parent (%d)\n", pid);
	}
	// close(fd[0]);
	return;

	/* get_heredoc("EOF");
	get_heredoc("test");
	if (!input)
	{
		printf("give me a path\n");
		return;
	} */

	// printf("test_heredoc = %d\n", test_heredoc());
	// printf("get_heredoc = %s\n", get_heredoc());

	// char *path = input->token;
	// printf("testing `%s`\n", path);

	// printf("infile = %d\n", check_infile(path));
	// printf("outfile = %d\n", check_outfile(path));
	// printf("append = %d\n", check_append(path));
}
