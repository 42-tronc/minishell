/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/06/01 09:53:26 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// debug functions
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

// might need to change the export and set to only print if there is a value, if not it is a export
void	check_command(t_data *data, t_token *input, int block)
{
	// printf("checking command in block %d\n", block);
	while (input && input->pipe_block == block)
	{
		// printf("checking %s being a %s\n", input->token, input->type);
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
			else if (ft_strcmp(input->token, "exit") == 0)
			{
				free(data->p);
				ft_exit(input->next);
			}
			else if (ft_strcmp(input->token, "export") == 0)
				printf("this needs a quick fix\n");
				// ft_export(data->env, input);
			else if (ft_strcmp(input->token, "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(input->token, "unset") == 0)
				ft_unset(&data->env, input);

			// TESTS
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


// need to stop if one check fails
// need to check if there is a pipe block after
void	exec_dispatch(t_data *data, t_token *input)
{
	int	block;

	block = 0;
	// printf("cmd block count = %d\n", data->cmd_block_count);
	while (input && block < data->cmd_block_count)
	{
		// printf(RED "block=%d\ncurrent block %d\n" RESET, block, input->pipe_block);
		check_heredoc(data, input, block);
		check_infile(data, input, block);
		check_outfile(data, input, block);
		check_command(data, input, block); // will be changed
		// check if pipe after or not
		// if ()
		block++;
		while (block > input->pipe_block && input->next)
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
	data->cmd_block_count = 1;
	while (temp)
	{
		if (!ft_strcmp(temp->type, PIPE))
			data->cmd_block_count++;
		temp = temp->next;
	}
	// data->cmd_block = NULL;
	data->cmd_block = ft_calloc(data->cmd_block_count + 1, sizeof(t_cmd_block*));
	if (!data->cmd_block)
		return (MALLOC_ERROR);
	i = 0;
	while (i < data->cmd_block_count)
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

	(void)argv;
	if (argc != 1)
		return ((void)printf("Don't put args !\n"), 1);
	data = ft_calloc(1, sizeof(t_data));
	data->env = fill_env(envp);
	get_signal();
	while (1)
	{
		data->tokens = getting_line(data);
		if (data->tokens && !prepare_token(data))
		{
			if (init_data(data))
				exit(FAILURE);

			exec_dispatch(data, data->tokens);
			// print_tokens_linked_list(data->tokens);

			// for (int i = 0; data->cmd_block[i]; i++)
			// 	printf("i=%d\tin=%d\tout=%d\n", i, data->cmd_block[i]->in_fd, data->cmd_block[i]->out_fd);
			free_token(data->tokens);
		}
		free(data->p);
	}
	free_list(data->env);
	return (0);
}
