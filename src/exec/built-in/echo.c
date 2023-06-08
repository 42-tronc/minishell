/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/06/08 09:20:42 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODO

`-n -n`
	should not display anything

`-nnnn`
	should not display anything

`-n -n Hola`
	`Hola`

`-p`
	`-p`

`Hola -n`
	`Hola -n`

``
	``

`/n hola`
	`n hola`

 */

/**
 * @brief checks if a newline is needed by looking for any '-n' or '-nnnn...'
 *
 * @param str string to check
 * @return int 1 if needed so no `-n` found, else 0
 */
static int	need_newline(char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '-')
	{
		if (str && str[1] == 'n')
		{
			i++;
			while (str[i] && str[i] == 'n')
				i++;
			if (!str[i])
				return (0);
		}
	}
	return (1);
}

void	create_subshell(void (*function)(t_token*, int), t_data *data, t_token *input, int block)
{
    pid_t pid = fork();

    if (pid == -1)
	{
        // Fork failed
        perror("fork");
        return;
    }
	else if (pid == 0)
	{
        // Child process
		check_output(data, block);
        function(input, block);  // Execute the specified function in the subshell
        _exit(0);    // Terminate the child process
    }
	else
	{
        // Parent process
        int status;
        waitpid(pid, &status, 0);  // Wait for the child process to finish
        printf("Subshell execution complete %d\n", status);
    }
}

void	echo_print(t_token *input, int block)
{
	int	first;
	int	newline;

	newline = 1;
	// if there is a `-n`, set the newline to 0
	if (input && input->token && !need_newline(input->token))
	{
		newline = 0;
		input = input->next;
	}
	// if there is a `-n`, skip every -n
	while (input && input->token && !need_newline(input->token))
		input = input->next;
	first = 1;
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			// printf("%s", input->token);
			write(STDOUT_FILENO, input->token, ft_strlen(input->token));
			first = 0;
		}
		if (input->next && ft_strcmp(input->next->type, ARG) == 0 && !first)
			// printf(" ");
			write(STDOUT_FILENO, " ", 1);
		input = input->next;
	}
	// printf("`");
	if (newline)
		// printf("\n");
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief print a string or an array of strings
 *
 * @param ac nb of args passed
 * @param av array of args to print
 */
void	ft_echo(t_data *data, t_token *input, int block)
{
	// only print arguments
	// while (input && ft_strcmp(input->type, PIPE) != 0)
	// check_output(data, block);
	// 	create_subshell(ft_echo, data, input, block);

	// echo_print(input, block, newline);
	create_subshell(echo_print, data, input, block);
}
