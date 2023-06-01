/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:08:49 by croy              #+#    #+#             */
/*   Updated: 2023/06/01 09:54:26 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
NEED

free everything then exit with proper exit code
check if nb
need to divide something by something to get real exit code
 */
#include "minishell.h"

void	ft_exit(t_token *input)
{
	int	exit_code;

	printf("error code %s\n", input->token);
	if (!input)
		exit(0);
	exit_code = ft_atoi(input->token);
	while (exit_code < 0)
	{
		exit_code = exit_code + 256;
	}
	exit_code = exit_code % 256;
	exit(exit_code);
}
