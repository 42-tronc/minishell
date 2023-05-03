/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/05/03 13:32:54 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_dispatch(t_data *data, t_token *input)
{
	while (input)
	{
		// if (!input->token_id)
		// {
		// printf("Token id = %s\n", input->token_id);
		// 	break;
		// }
		if (ft_strcmp(input->token_id, CMD) == 0)
		{
			if (ft_strcmp(input->token, "cd") == 0)
				ft_cd(data->env, input->next->token);
			else if (ft_strcmp(input->token, "echo") == 0)
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

int	main(int argc, char **argv, char **envp)
{
	t_data 		*data;
	t_token		*tokens;
	t_parsing	p;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	data->env = fill_env(envp);
	while (1)
	{
		tokens = getting_line(&p);
		p.env = fill_env(envp);
		expand_tokens(&tokens, &p);
		id_tokens(&tokens);
		// print_tokens_linked_list(tokens);

		exec_dispatch(data, tokens);

		free_token(tokens);
		free_list(p.env);
	}
	return (0);
}
