/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:31:40 by arthurasced       #+#    #+#             */
/*   Updated: 2023/03/31 11:37:17 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_token_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst && !*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_token	*ft_lstnew_token(void *content)
{
	t_token	*dst;

	dst = malloc(sizeof(t_token));
	if (!dst)
		return (NULL);
	if (dst)
	{
		dst->token = content;
		dst->next = NULL;
	}
	return (dst);
}

void	getting_line(t_token *tokens)
{
	char	*str;
	
	(void)tokens;
	str = ft_calloc(1, sizeof(char));
	while (1)
	{
		str = gnl_str_join(str, readline("minishell>"));
		printf("%s\n", str);
	}
}

int	main(void)
{
	t_token	*tokens;
	
	tokens = NULL;
	getting_line(tokens);
	ft_printf("Hello\n");
	return (0);
}
