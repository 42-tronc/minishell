/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:19:54 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/03 11:20:19 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_token	*tokens = NULL;
	
	// *tokens = NULL;
	getting_line(tokens);
	printf("Hello\n");
	return (0);
}