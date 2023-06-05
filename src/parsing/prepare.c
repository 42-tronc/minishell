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

void	prepare_token(t_data *data)
{
	expand_tokens(&data->tokens, data);
	expand_tilde(&data->tokens, data);
	remove_quotes(&data->tokens, data);
	id_tokens(&data->tokens, NULL);
}
