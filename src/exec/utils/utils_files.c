/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:28 by croy              #+#    #+#             */
/*   Updated: 2023/06/29 07:56:16 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if the infile/heredoc is the last of the command block
 *
 * @param input token starting where infile/heredoc is
 * @param block which command block to check
 * @return int 1 if it is the last input, 0 if not
 */
static int	is_last_input(t_token *input, int block)
{
	int	is_last;

	is_last = 1;
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, INFILE) == 0 || ft_strcmp(input->type,
				HERE_DOC) == 0)
			return (0);
		input = input->next;
	}
	return (is_last);
}

/**
 * @brief opens the heredoc and records the output if needed or dry run it
 *
 * @param data t_data struct with every var in it
 * @param input token starting where heredoc is
 * @param block which command block to check
 */
static void	open_heredoc(t_data *data, t_token *input, int block)
{
	char	*line;
	int		is_last;

	is_last = is_last_input(input, block);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document delimited by EOF (wanted `%s')\n",
				input->token);
			break ;
		}
		else if (ft_strcmp(line, input->token) == 0)
			break ;
		else if (is_last)
			data->cmd_block[block]->heredoc = ft_strjoin_heredoc(\
				data->cmd_block[block]->heredoc, line);
	}
}

/**
 * @brief checks and open the heredoc if one is detected
 *
 * @param data t_data struct with every var in it
 * @param input token from the very start
 * @param block which command block to check
 */
void	check_heredoc(t_data *data, t_token *input, int block)
{
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, LIMITER) == 0)
			open_heredoc(data, input, block);
		input = input->next;
	}
	return ;
}

int	check_infile(t_data *data, t_token *input, int block)
{
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, INFILE) == 0)
		{
			if (data->cmd_block[block]->in_fd >= 0)
				close(data->cmd_block[block]->in_fd);
			data->cmd_block[block]->in_fd = open(input->token, O_RDONLY);
			if (data->cmd_block[block]->in_fd == -1)
			{
				perror(BOLD RED "open" RESET);
				g_ret_value = 1;
				return (-1);
			}
		}
		input = input->next;
	}
	return (0);
}

int	check_outfile(t_data *data, t_token *input, int block)
{
	int	flags;

	flags = (O_WRONLY | O_CREAT | O_TRUNC);
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, OUTFILE) == 0 || ft_strcmp(input->type,
				APPEND) == 0)
		{
			if (ft_strcmp(input->type, APPEND) == 0)
				flags = (O_WRONLY | O_CREAT | O_APPEND);
			if (data->cmd_block[block]->out_fd >= 0)
				close(data->cmd_block[block]->out_fd);
			data->cmd_block[block]->out_fd = open(input->token, flags, 0777);
			if (data->cmd_block[block]->out_fd == -1)
			{
				perror(BOLD RED "open" RESET);
				g_ret_value = 1;
				return (-1);
			}
		}
		input = input->next;
	}
	return (0);
}
