/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:50:07 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/24 10:54:00 by croy             ###   ########lyon.fr   */
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
		temp->type = CHEVRON_L;
	else if (temp->token[0] == '<' && temp->token[1] == '<')
		temp->type = HERE_DOC;
	else if (temp->token[0] == '>' && temp->token[1] == '\0')
		temp->type = MY_NULL;
	else if (temp->token[0] == '>' && temp->token[1] == '>')
		temp->type = MY_NULL;
	else if (temp->token[0] == '|')
		temp->type = MY_NULL;
	else
		temp->type = CMD;
	return (1);
}
