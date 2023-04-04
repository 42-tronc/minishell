/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:19:54 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/04 14:17:45 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens_linked_list(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("___%s___\n", temp->token);
		temp = temp->next;
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	// t_token		*tokens;
// 	t_parsing	data;
// 	t_list		*list;

// 	data.begin = 0;
// 	data.end = 0;
// 	data.quote = 0;
// 	data.d_quote = 0;
// 	data.in_word = 0;
// 	(void)argc;
// 	(void)argv;
// 	list = get_envp(envp);
// 	print_list(list);
// 	//tokens = getting_line(&data);
// 	// print_tokens_linked_list(tokens);
// 	return (0);
// }
