/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:11:04 by croy              #+#    #+#             */
/*   Updated: 2023/06/13 14:15:53 by croy             ###   ########lyon.fr   */
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

int	check_output(t_data *data, int block, char *cmd_path)
{
	printf(RED"OUTPUT block %d/%d%s\n", block + 1, data->cmd_block_count, RESET);
	if (data->cmd_block[block]->out_fd > 0)
	{
		if (dup2(data->cmd_block[block]->out_fd, STDOUT_FILENO) == -1)
			return (FAILURE);
		close(data->cmd_block[block]->out_fd);
	}
	// if not the last block, put output to pipe
	else if (block < data->cmd_block_count - 1)
	{
		printf("PIPE: STDOUT -> [%d][%d] for %s\n", block, STDOUT_FILENO, cmd_path);
		if (dup2(data->cmd_block[block]->pipe_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
			return (FAILURE);
		// close(data->cmd_block[block]->pipe_fd[STDOUT_FILENO]);
	}
	// sinon STDOUT to STDOUT

	return (0);
}

int	check_input(t_data *data, int block, char *cmd_path)
{
	printf(RED"INPUT block %d/%d%s\n", block + 1, data->cmd_block_count, RESET);
	if (data->cmd_block[block]->in_fd > 0)
	{
		if (dup2(data->cmd_block[block]->in_fd, STDIN_FILENO) == -1)
			return (FAILURE);
		close(data->cmd_block[block]->in_fd);
	}
	// if not the first block, then get the input of last pipe
	else if (block > 0)
	{
		block -= 1;
		printf("PIPE: STDIN <- [%d][%d] for %s\n", block, STDIN_FILENO, cmd_path);
		if (dup2(data->cmd_block[block]->pipe_fd[STDIN_FILENO], STDIN_FILENO) == -1)
			return (FAILURE);
		close(data->cmd_block[block]->pipe_fd[STDIN_FILENO]);
	}
	// sinon STDIN to STDIN

	return (0);
}

int	create_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd_block_count < 1)
		return (SUCCESS);
	// printf("cmd block count = %d\n", data->cmd_block_count);
	// data->cmd_block
	while (i < data->cmd_block_count - 1)
	{
		if (pipe(data->cmd_block[i]->pipe_fd) == -1)
			return (FAILURE);
		printf("pipe[%d][0]=%d\t pipe[%d][1]=%d\n", i, data->cmd_block[i]->pipe_fd[0], i, data->cmd_block[i]->pipe_fd[1]);
		i++;
		// printf("pipe[%d][0]=%d\t pipe[%d][1]=%d\n", i, data->cmd_block[i]->pipe_fd[0], i, data->cmd_block[i]->pipe_fd[1]);
	}
	printf("created %d pipes\n", i);
	return (SUCCESS);
}

void exec_command(t_data *data, t_token *input, int block) {
    pid_t pid;
    char *command_path;
    char **command_args;

    command_path = get_validpath(data, input);
    if (!command_path) {
        printf(RED BOLD "%s: %scommand not found (blocked the rest of the exec)\n", input->token, NO_BOLD);
        return; // will need to close fd here if opened
    }
	// printf(YELLOW"Path: %s`%s`\n"RESET, BOLD, command_path); // debug

    command_args = get_cmd_args(input, command_path);

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // child process
        check_input(data, block, command_path);
        check_output(data, block, command_path);

        execve(command_path, command_args, NULL);
        printf(BOLD RED "%s: %scommand not found\n", input->token, NO_BOLD);
        exit(EXIT_FAILURE);
    } else {
        // parent process
        int wstatus;

		if (data->cmd_block[block]->pipe_fd[0] > 0 && block > 0)
			close(data->cmd_block[block - 1]->pipe_fd[0]); // Close the read end of the pipe in the child
		if (data->cmd_block[block]->pipe_fd[1] > 0 && block < data->cmd_block_count - 1)
			close(data->cmd_block[block]->pipe_fd[1]); // Close the write end of the pipe in the parent
        waitpid(pid, &wstatus, 0);


        printf("Subshell execv complete %d\n", wstatus);
        if (WIFEXITED(wstatus)) {
            int statuscode = WEXITSTATUS(wstatus);
            if (statuscode == 0)
                printf(BOLD GREEN "%s: %ssuccess\n" RESET, input->token, NO_BOLD);
            else
                printf("failure with %d\n", statuscode);
        }
    }
}


/* void	exec_command(t_data *data, t_token *input, int block)
{
	pid_t	pid;
	char	*command_path;
	char	**command_args;

	command_path = get_validpath(data, input);
	if (!command_path)
	{
		printf(RED BOLD"%s: %scommand not found (blocked the rest of the exec)\n", input->token, NO_BOLD);
		return; // will need to close fd here if opened
	}
	command_args = get_cmd_args(input, command_path);

	// --- START DEBUG
	// Print the array elements for verification
	// for (int i = 0; command_args[i]; i++)
	// 	printf("arg[%d]\t`%s`\n", i, command_args[i]);
	// --- END DEBUG

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		// child process
		check_input(data, block, command_path);
		check_output(data, block, command_path);
		// if (command_path)
		execve(command_path, command_args, NULL);
		printf(BOLD RED"%s: %scommand not found\n", input->token, NO_BOLD);
	}
	else
	{
		// parent process

		// this might be shit
		int	wstatus;
		waitpid(pid, &wstatus, 0);
		// close(data->cmd_block[block]->pipe_fd[STDIN_FILENO]);
		// close(data->cmd_block[block]->pipe_fd[STDOUT_FILENO]);
		printf("Subshell execv complete %d\n", wstatus);
		// printf("wstatus %d\n", wstatus);
		if (WIFEXITED(wstatus))
		{
			int statuscode = WEXITSTATUS(wstatus);
			if (statuscode == 0)
				printf(BOLD GREEN"%s: %ssuccess\n"RESET, input->token, NO_BOLD);
			else
				printf("failure with %d\n", statuscode);
		}
	}
	return ;
}
 */
