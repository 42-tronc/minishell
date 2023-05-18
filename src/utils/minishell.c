/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/05/18 08:50:00 by croy             ###   ########lyon.fr   */
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
		printf("Type : %s && token[%d]:'%s' in pipe block:%d\n",temp->token_id, i++, temp->token, temp->pipe_block);
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

/*
Will need to check back every command to see if they work properly with weird cases

check each block

	check for infiles
		put every infile in a linked list
	check for outfiles
		put every outfile in a linked list
	check for commands
*/

void	is_infile(t_data *data, t_token *input, t_cmd_block *block)
{
	(void) data;
	block->in_fd = -2;
	while (input)
	{
		if (ft_strcmp(input->token, PIPE) == 0)
			break;
		if (ft_strcmp(input->token, INFILE) == 0)
		{
			block->in_fd = open(input->token, O_RDONLY);
			if (block->in_fd == -1)
			{
				perror("open");
				return;
			}
		}
		input = input->next;
	}
}

void	exec_dispatch(t_data *data, t_token *input)
{
	t_cmd_block	*block;

	// check_infiles
	// check_outfiles
	// check_command
	while (input)
	{
		if (input->token_id && ft_strcmp(input->token_id, CMD) == 0)
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
			count_pipes(data);
			// printf("pipe = %d\n", data->pipe_count);
			// print_tokens_linked_list(data->tokens);
			exec_dispatch(data, data->tokens);
			free_token(data->tokens);
			free(data->p);
		}
	}
	free_list(data->env);
	return (0);
}
