/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:19:57 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/27 14:43:46 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens_linked_list(t_token *head, t_parsing *p)
{
	t_token	*temp;
	// t_token	*last;
	int		i;

	(void)p;
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

void	print_env(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s et ", (char *)temp->var);
		printf("%s\n", (char *)temp->value);
		temp = temp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*tokens;
	t_parsing	p;

	(void)argc;
	(void)argv;
	p.env = fill_env(envp);
	while (1)
	{
		tokens = getting_line(&p);
		expand_tokens(&tokens, &p);
		id_tokens(&tokens, &p);
		print_tokens_linked_list(tokens, &p);

		// exec_dispatch(tokens);

		// print_env(p.env);
		free_token(tokens);
		free_list(p.env);
	}
	return (0);
}
