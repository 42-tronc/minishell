/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:07:28 by croy              #+#    #+#             */
/*   Updated: 2023/05/25 13:05:15 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last_input(t_token *input, int block)
{
	int	is_last;

	is_last = 1;
	printf("starting with %s\n", input->token);
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, INFILE) == 0 || ft_strcmp(input->type, HERE_DOC) == 0)
			return (0);
		input = input->next;
	}
	return (is_last);
}

void	open_heredoc(t_data *data, t_token *input, int block)
{
	char	*line;
	int		is_last;

	is_last = is_last_input(input, block);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("lillaskallet: warning: here-document delimited by end-of-file (wanted `%s')\n", input->token);
			break;
		}
		if (ft_strcmp(line, input->token) == 0)
		{
			printf("found the EOF\n"); // DELETE
			break;
		}
		if (is_last)
			data->cmd_block[block]->heredoc = ft_strjoin_heredoc(data->cmd_block[block]->heredoc, line);
	}

	// DEBUG MSG
	if (!data->cmd_block[block]->heredoc) // DELETE
		printf(RED"this was not saved\n"RESET); // DELETE
	else // DELETE
		printf("document=\n%s`%s`\n"RESET, GREEN, data->cmd_block[block]->heredoc); // DELETE
	// DEBUG END
}

int	check_heredoc(t_data *data, t_token *input, int block)
{
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, LIMITER) == 0)
			open_heredoc(data, input, block);
		// else // DELETE
		// 	printf(RED"%s is a %s\n"RESET, input->token, input->type); // DELETE
		input = input->next;
	}
	return (0);
}

int	check_infile(t_data *data, t_token *input, int block)
{
	while (input && input->pipe_block == block)
	{
		// printf("Checking block %s%d\n"RESET, BOLD, block); // DELETE
		if (ft_strcmp(input->type, INFILE) == 0)
		{
			printf("INFILE: %s%s%s\n", BOLD, input->token, NO_BOLD); // DELETE

			// close previous file if it was opened // DELETE
			if (data->cmd_block[block]->in_fd >= 0)
				close(data->cmd_block[block]->in_fd);

			data->cmd_block[block]->in_fd = open(input->token, O_RDONLY);
			if (data->cmd_block[block]->in_fd == -1) // REFACTOR
			{
				perror(BOLD RED"open"RESET);
				return (-1);
			}

			else // DELETE
				printf(GREEN"OK: %s%s\n"RESET, BOLD, input->token); // DELETE
		}
		// else
		// 	printf(RED"%s is a %s\n"RESET, input->token, input->type);
		input = input->next;
	}
	return (0);
}

int	check_outfile(t_data *data, t_token *input, int block)
{
	int	flags;

	// set default flags as trunc
	flags = (O_WRONLY | O_CREAT | O_TRUNC);
	while (input && input->pipe_block == block)
	{
		if (ft_strcmp(input->type, OUTFILE) == 0 || ft_strcmp(input->type, APPEND) == 0)
		{
			printf("%s is a %s\n"RESET, input->token, input->type);
			printf("OUTFILE: %s%s%s\n", BOLD, input->token, NO_BOLD);

			// change flags for append if needed
			if(ft_strcmp(input->type, APPEND) == 0)
				flags = (O_WRONLY | O_CREAT | O_APPEND);

			// close previous file if it was opened
			if (data->cmd_block[block]->out_fd >= 0)
				close(data->cmd_block[block]->out_fd);
			// else
			// 	printf("not opened\n");

			data->cmd_block[block]->out_fd = open(input->token, flags);
			if (data->cmd_block[block]->out_fd == -1)
			{
				perror(BOLD RED "open" RESET);
				return (-1);
			}
			else
				printf(GREEN "OK: %s%s\n\n" RESET, BOLD, input->token);
		}
		input = input->next;
	}
	return (0);
}
