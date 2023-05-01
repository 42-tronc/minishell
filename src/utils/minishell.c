/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:37:22 by croy              #+#    #+#             */
/*   Updated: 2023/04/27 16:58:18 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_dispatch(t_data *data, t_token *input)
{
	// while (input)
	if (input->token_id == "command")
	{
		if (ft_strcmp(input->token, "echo") == 0)
			printf("echo in the building\n");
			// ft_echo()
		else if (ft_strcmp(input->token, "env") == 0)
			ft_env(data->env);
	// printf("input = `%s`\n", input->token);
		input = input->next;
	}
	// ft_env(data->env);
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
