/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:19:54 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/03 14:18:52 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens_linked_list(t_token* head) {
	t_token *temp;

	temp = head;
    while (temp != NULL) {
        printf("token:%s\n", temp->token);
        temp = temp->next;
    }
}

int	main(void)
{
	t_token	*tokens;

	tokens = getting_line();
	print_tokens_linked_list(tokens);
	return (0);
}
