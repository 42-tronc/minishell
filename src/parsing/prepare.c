/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:57:28 by aascedu           #+#    #+#             */
/*   Updated: 2023/08/04 18:35:16 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("temp[%i]:%s et type:%s\n", i, tokens->token, tokens->type);
		i++;
		tokens = tokens->next;
	}
}

int	prepare_token(t_data *data)
{
	id_tokens(&data->tokens, NULL);
	check_in_quotes(&data->tokens, data);
	if (expand_tokens(&data->tokens, data))
		return (1);
	if (cutting_expand(data))
		return (1);
	id_tokens(&data->tokens, NULL);
	if (expand_tilde(&data->tokens, data))
		return (1);
	if (!need_to_new(data->tokens) \
		&& replace_list(data, NULL, ft_tokensize(data->tokens)))
		return (1);
	id_tokens(&data->tokens, NULL);
	if (remove_quotes(&data->tokens, data))
		return (1);
	if (syntax_error(data))
		return (1);
	return (0);
}
