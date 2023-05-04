/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/05/04 15:28:26 by croy             ###   ########lyon.fr   */
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
		if (ft_strcmp(input->token_id, CMD) == 0)
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
				ft_getpaths(data);
				int i = 0;
				while (data->paths[i])
				{
					printf("path[%d]=`%s`\n", i, data->paths[i]);
					i++;
				}
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
				printf("%s is not a command\n", input->token);
		}
		input = input->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data 		*data;
	t_token		*tokens;
	t_parsing	p;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	data->env = fill_env(envp);
	p.env = fill_env(envp);
	while (1)
	{
		tokens = getting_line(&p);
		expand_tokens(&tokens, data);
		id_tokens(&tokens);
		// print_tokens_linked_list(tokens);

		exec_dispatch(data, tokens);

		free_token(tokens);
	}
	free_list(p.env);
	return (0);
}
