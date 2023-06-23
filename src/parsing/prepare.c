/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:57:28 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/23 11:37:40 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_token(t_data *data)
{
	check_in_quotes(&data->tokens, data);
	print_tokens_linked_list(data->tokens);
	if (expand_tokens(&data->tokens, data))
		return (1);
	print_tokens_linked_list(data->tokens);
	if (cutting_expand(data))
		return (1);
	print_tokens_linked_list(data->tokens);
	if (expand_tilde(&data->tokens, data))
		return (1);
	if (!need_to_new(data->tokens) \
		&& replace_list(data, NULL, ft_tokensize(data->tokens)))
	{
		data->status = 0;
		return (1);
	}
	id_tokens(&data->tokens, NULL);
	if (remove_quotes(&data->tokens, data))
		return (1);
	if (syntax_error(data))
		return (1);
	print_tokens_linked_list(data->tokens);
	return (0);
}
