/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/05/02 17:12:40 by croy             ###   ########lyon.fr   */
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

void	exec_dispatch(t_data *data, t_token *input)
{
	while (input)
	{
		if (ft_strcmp(input->token_id, "command") == 0)
		{
			if (ft_strcmp(input->token, "cd") == 0)
				ft_cd(data->env, input->next->token);
			if (ft_strcmp(input->token, "echo") == 0)
				ft_echo(input);
			else if (ft_strcmp(input->token, "env") == 0)
				ft_env(data->env);
			else if (ft_strcmp(input->token, "fork") == 0)
				ft_fork();
			else
				printf("%s is not a command\n", input->token);
		}
		input = input->next;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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
		expand_tokens(&data->tokens, data);
		id_tokens(&data->tokens);
		print_tokens_linked_list(data->tokens);

		exec_dispatch(data, data->tokens);

		free_token(data->tokens);
		free(data->p);
	}
	free_list(data->env);
	return (0);
}
