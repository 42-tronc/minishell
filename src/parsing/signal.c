/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:17:36 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/20 15:30:48 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_program(t_data *data)
{
	free(data->p);
	free_list(data->env);
	free(data);
	printf("exit\n");
	rl_clear_history();
	exit (g_ret_value);
}

void	redisplay_prompt(int sig)
{
	(void)sig;
	g_ret_value = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	get_signal_prompt(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &redisplay_prompt);
}

void	get_signal_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	get_signal_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signals_heredoc);
}
