/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/06/07 13:29:07 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getpaths(t_data *data)
{
	char	*paths;

	paths = ft_getenv(data->env, "PATH");
	if (!paths)
		return (1);
	data->paths = split_paths(paths, ':');
	return (0);
}

/**
 * @brief Gets the path of the command passed as input
 *
 * @param data t_data struct with every var in it
 * @param input token with the command
 * @return char* path of the command or NULL if not found
 */
char	*get_validpath(t_data *data, t_token *input)
{
	int		i;
	int		error_access;
	char	*command_path;

	i = 0;
	error_access = 1;
	if (!input)
		return (NULL);
	if (ft_strchr(input->token, '/') && !access(input->token, X_OK))
		return (input->token);
	// Update paths in case it changed
	if (ft_getpaths(data))
		return (NULL);
	while (data->paths[i] && error_access)
	{
		// error_access = 0;
		command_path = ft_strjoin(data->paths[i], input->token);
		if (!command_path)
			return (NULL);
		// printf("checking %s\n", command_path);
		error_access = access(command_path, X_OK);
		if (!error_access)
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Counts the number of arguments + cmd to malloc
 *
 * @param input
 * @return size_t cmd + args count
 */
static size_t	_count_cmd_args(t_token *input)
{
	size_t	size;

	size = 0;
	if (ft_strcmp(input->type, CMD) == 0)
		size++;
	input = input->next;
	while (input)
	{
		if (ft_strcmp(input->type, PIPE) == 0)
			break ;
		else if (ft_strcmp(input->type, ARG) == 0)
			size++;
		// printf(BOLD YELLOW "`%s`\t%shas type: %s%s\tin block %s%d%s\n",
			// input->token, NO_BOLD, BOLD, input->type, BOLD, input->pipe_block, NO_BOLD);
		input = input->next;
	}
	// printf(BOLD YELLOW"%ld %sargument(s)\n"RESET, size, NO_BOLD);
	return (size);
}

char	**get_cmd_args(t_token *input, char *command_path)
{
	size_t	i;
	size_t	size;
	char	**array;

	// printf(BOLD BLUE"\n get_cmd_args\n"RESET); // debug
	if (!input)
	{
		printf(BOLD RED "No arg\n" RESET);
		return (NULL);
	}
	size = _count_cmd_args(input);
	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	// printf(GREEN"\t󰍛 FT_CALLOC\n"RESET); // debug
	i = 1;
	input = input->next;
	array[0] = command_path;
	// printf("size=%ld\n", size);
	while (input && i < size)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			array[i] = ft_strdup(input->token);
			// printf("array[%ld]=%s\n", i, array[i]);
			i++;
		}
		input = input->next;
	}
	return (array);
}

static int	to_outfile(t_data *data, int block)
{
	if (data->cmd_block[block]->out_fd > 0)
	{
		if (dup2(data->cmd_block[block]->out_fd, STDOUT_FILENO) == -1)
			return (FAILURE);
		close(data->cmd_block[block]->out_fd);
	}
	return (0);
}

void	exec_command(t_data *data, t_token *input, int block)
{
	// printf(BOLD BLUE"\n exec_command\n"RESET); // debug
	(void) data;
	int		fd[2];
	// will need fd[pipe_count][2];
	int		pid = 0;
	char	*command_path;
	char	**command_args;

	/* if (!input)
	{
		printf(BOLD RED"No input\n"RESET);
		return ;
	} */
	command_path = get_validpath(data, input);
	if (!command_path)
	{
		printf(RED BOLD"%s: %scommand not found (blocked the rest of the exec)\n", input->token, NO_BOLD);
		// will need to close fd here if opened
		return;
	}
	printf(YELLOW"Path: %s`%s`\n"RESET, BOLD, command_path); // debug

	command_args = get_cmd_args(input, command_path);
	// printf(BOLD GREEN" get_cmd_args%s\n", RESET); // debug

	// --- START DEBUG
	// Print the array elements for verification
	// for (int i = 0; command_args[i]; i++)
	// 	printf("arg[%d]\t`%s`\n", i, command_args[i]);
	// --- END DEBUG

	// exec part
	// pas si c le dernier
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// printf(GREEN"\t󰟥 PIPE\n"RESET);

	// will need a loop
	/*
	while (i < pipecount)
	{
		if (pipe(fd[i]) < 0)
		{
			close previous pipe if i > 0
			and return error
		}
	}
	 */

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		// child process
		// printf(GREEN"\t FORK%s\n", MAGENTA);
		// dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);

		to_outfile(data, block);
		// if (command_path)
			execve(command_path, command_args, NULL);

		// perror(BOLD RED" execve"RESET);
		// printf("something's wrong i can feel it\n");
		printf(BOLD RED"%s: %scommand not found\n", input->token, NO_BOLD);

	}
	else
	{
		close(fd[0]);
		close(fd[1]);

		// this might be shit
		int	wstatus;
		wait(&wstatus);
		// printf("wstatus %d\n", wstatus);
		if (WIFEXITED(wstatus))
		{
			int statuscode = WEXITSTATUS(wstatus);
			if (statuscode == 0)
				printf(BOLD GREEN"%s: %ssuccess\n"RESET, input->token, NO_BOLD);
			else
				printf("failure with %d\n", statuscode);
		}
		// probably is
	}
	// printf(BOLD GREEN" exec_command\n\n"RESET);
	return ;
}
