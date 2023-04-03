/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:31:40 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/03 13:49:38 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (lst == NULL)
	{
		return ;
	}
	temp = *lst;
	if (!temp)
	{
		*lst = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_token	*ft_tokennew(void *content)
{
	t_token	*dst;

	dst = malloc(sizeof(t_token));
	if (!dst)
		return (NULL);
	if (dst)
	{
		dst->token = (char *)content;
		dst->next = NULL;
	}
	return (dst);
}

void	add_token(t_token **tokens, char *str, int begin, int end)
{
	char	*token;
	int		i;

	token = malloc(sizeof(char) * (end - begin + 1));
	if (!token)
		return ;
	i = 0;
	while (begin < end)
	{
		token[i] = str[begin];
		begin++;
		i++;
	}
	token[i] = '\0';
	ft_tokenadd_back(tokens, ft_tokennew(token));
}

void	getting_line(t_token *tokens)
{
	int		i;
	int		j;
	char	*str;

	str = readline("minishell>");
	i = 0;
	while (str && str[i])
	{
		j = i;
		while (str[i] != ' ' && str[i])
			i++;
		add_token(&tokens, str, j, i);
		while (str[i] == ' ' && str[i])
			i++;
	}
	free(str);
}
