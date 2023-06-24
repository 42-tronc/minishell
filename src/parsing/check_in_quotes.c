/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:52:15 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/23 11:28:29 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_in_quotes(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
	return (0);
}

void	check_in_quotes(t_token **tokens, t_data *data)
{
	t_token	*temp;

	(void)data;
	temp = *tokens;
	while (temp)
	{
		if (token_in_quotes(temp->token))
			temp->in_quote = 1;
		temp = temp->next;
	}
}
