/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:08:45 by aascedu           #+#    #+#             */
/*   Updated: 2023/07/17 15:08:46 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_here_doc(t_data *data, t_token *input, char *line, int block)
{
	if (!line)
	{
		printf("warning: here-document delimited by EOF (wanted `%s')\n",
			input->token);
		return (1);
	}
	else if (ft_strcmp(line, input->token) == 0)
	{
		free(line);
		return (1);
	}
	else if (data->cmd_block[block]->is_last)
		data->cmd_block[block]->heredoc = ft_strjoin_heredoc(\
			data->cmd_block[block]->heredoc, line);
	else
		free(line);
	return (0);
}
