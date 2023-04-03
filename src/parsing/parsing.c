/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:19:54 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/03 13:50:01 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_tokens_linked_list(t_token* head) {
// 	t_token *temp;

// 	temp = head;
//     while (temp != NULL) {
//         printf("%s\n", temp->token);
//         temp = temp->next;
//     }
// }

int	main(void)
{
	t_token	*tokens;

	tokens = NULL;
	getting_line(tokens);
	printf("Hello\n");
	printf("%p\n", tokens);
	return (0);
}
