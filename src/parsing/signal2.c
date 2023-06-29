/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:18:45 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/29 14:19:43 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signal)
{
	(void)signal;
	g_ret_value = 130;
	printf("\n");
}

void	handle_sigquit(int signal)
{
	(void)signal;
	g_ret_value = 131;
	printf("Quit (core dumped)\n");
	exit (g_ret_value);
}

void	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		g_ret_value = 130;
		printf("\n");
	}
	else if (signal == SIGQUIT)
	{
		g_ret_value = 131;
		printf("Quit (core dumped)\n");
	}
}
