/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:50:07 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/27 10:49:28 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(t_token *temp)
{
	if (temp->token[0] == '|' || temp->token[0] == '<' \
	|| temp->token[0] == '>')
		return (1);
	return (0);
}

int	first_token(t_token *temp)
{
	if (temp->token[0] == '<' && temp->token[1] == '\0')
		temp->token_id = CHEVRON_L;
	else if (temp->token[0] == '>' && temp->token[1] == '\0')
		return (1);
	else if (temp->token[0] == '<' && temp->token[1] == '<')
		temp->token_id = HERE_DOC;
	else if (temp->token[0] == '|')
		return (1);
	else if (temp->token[0] == '>' && temp->token[1] == '>')
		return (1);
	else
		temp->token_id = CMD;
	return (1);
}
