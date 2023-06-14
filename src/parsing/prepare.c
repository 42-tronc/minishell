/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:57:28 by aascedu           #+#    #+#             */
/*   Updated: 2023/05/31 10:57:30 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_token(t_data *data)
{
	id_tokens(&data->tokens, NULL);
	if (expand_tokens(data->tokens, data) == 1)
		return (1);
	if (expand_tilde(&data->tokens, data) == 1)
		return (1);
	if (remove_quotes(&data->tokens, data) == 1)
		return (1);
	if (syntax_error(data) == 1)
		return (1);
	return (0);
}
