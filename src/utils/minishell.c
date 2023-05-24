/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/05/24 12:51:17 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens_linked_list(t_token *head)
{
	t_token	*temp;
	// t_token	*last;
	int		i;

	temp = head;
	// last = NULL;
	i = 0;
	while (temp != NULL)
	{
		printf("Type : %s && token[%d]:'%s' in pipe block:%d\n",temp->type, i++, temp->token, temp->pipe_block);
		// if (temp->next == NULL)
		// 	last = temp;
		temp = temp->next;
	}
	// while (last)
	// {
	// 	printf("token prev:%s\n", last->token_id);
	// 	last = last->prev;
	// }
}

int	check_infile(t_data *data, t_token *input, int block)
{
	(void) data;
	while (input && input->pipe_block == block)
	{
		// printf("Checking block %s%d\n"RESET, BOLD, block);
		if (ft_strcmp(input->type, INFILE) == 0)
		{
			printf("INFILE: %s%s%s\n", BOLD, input->token, NO_BOLD);
			data->cmd_block[block]->in_fd = open(input->token, O_RDONLY);
			if (data->cmd_block[block]->in_fd == -1)
			{
				perror(BOLD RED"open"RESET);
				return (-1);
			}
			else
				printf(GREEN"OK: %s%s\n"RESET, BOLD, input->token);
		}
		// else
		// 	printf(RED"%s is a %s\n"RESET, input->token, input->type);
		input = input->next;
	}
	return (0);
}

void	exec_dispatch(t_data *data, t_token *input)
{
	// check_heredoc
	check_infile(data, input, 0);
	// check_outfiles
	// check_command

	while (input)
	{
		if (input->type && ft_strcmp(input->type, CMD) == 0)
		{
			if (ft_strcmp(input->token, "cd") == 0)
				ft_cd(data, input->next);
				// ft_cd(data->env, input->next);
				// ft_cd(data->env, input->next->token);
			else if (ft_strcmp(input->token, "echo") == 0)
				ft_echo(input->next);
			else if (ft_strcmp(input->token, "env") == 0)
				ft_env(data->env);
			// else if (ft_strcmp(input->token, "exit") == 0)
			// 	ft_exit;
			// else if (ft_strcmp(input->token, "export") == 0)
			// 	ft_export(data->env, input);
			else if (ft_strcmp(input->token, "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(input->token, "unset") == 0)
				ft_unset(&data->env, input);

			// TESTS
			else if (ft_strcmp(input->token, "xc") == 0)
			{
				// ft_getpaths(data);
				// printf("Path: `%s`\n", get_validpath(data, input->next));
				exec_command(data, input->next);


				// int i = 0;
				// while (data->paths[i])
				// {
				// 	printf("path[%d]=`%s`\n", i, data->paths[i]);
				// 	i++;
				// }
			}
			else if (ft_strcmp(input->token, "tf") == 0)
			{
				test_files(data, input->next);
			}
			else if (ft_strcmp(input->token, "test") == 0)
			{
				// ft_setenv(data->env, "SUDO_EDITOR", "not vim");
				ft_setenv(data->env, "LOLI", "Pretty sadge");
				// ft_setenv(data->env, "LAWL", "Very pepehands");
				ft_env(data->env);
				// ft_env(data->env);
				printf("\n\n\nHEYO\nLOLI=%s\n", ft_getenv(data->env, "LOLI"));
			}

			// BACK 2 NORMAL
			else
				exec_command(data, input);
				// printf("minishell: %s: command not found\n", input->token);
		}
		input = input->next;
	}
}

// void	free_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// will need to get the return value to somewhere
int	init_data(t_data *data)
{
	int		i;
	t_token	*temp;

	temp = data->tokens;
	data->pipe_count = 1;
	while (temp)
	{
		if (!ft_strcmp(temp->type, PIPE))
			data->pipe_count++;
		temp = temp->next;
	}
	// data->cmd_block = NULL;
	data->cmd_block = ft_calloc(data->pipe_count + 1, sizeof(t_cmd_block*));
	if (!data->cmd_block)
		return (MALLOC_ERROR);
	i = 0;
	while (i < data->pipe_count)
	{
		data->cmd_block[i] = ft_calloc(1, sizeof(t_cmd_block));
		data->cmd_block[i]->in_fd = -2;
		data->cmd_block[i]->out_fd = -2;
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data 	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	data->env = fill_env(envp);

	while (1)
	{
		data->tokens = getting_line(data);
		if (data->tokens)
		{
			expand_tokens(&data->tokens, data);
			id_tokens(&data->tokens);
			// print_tokens_linked_list(data->tokens);

			if (init_data(data))
				exit(FAILURE);

			exec_dispatch(data, data->tokens);

			// for (int i = 0; data->cmd_block[i]; i++)
			// 	printf("i=%d\tin=%d\tout=%d\n", i, data->cmd_block[i]->in_fd, data->cmd_block[i]->out_fd);
			free_token(data->tokens);
			free(data->p);
		}
	}
	free_list(data->env);
	return (0);
}
