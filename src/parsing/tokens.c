/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:31:40 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/03 11:19:35 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_token	*ft_tokennew(void *content)
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

void	add_token(t_token *tokens, char *str, int begin, int end)
{
	char	*token;

	token = malloc(sizeof(char) * (end - begin + 2));
	if (!token)
		return ;
	while (begin <= end)
	{
		token[begin] = str[begin];
		begin++;
	}
	token[begin] = '\0';
	ft_tokenadd_back(&tokens, ft_tokennew(token));
}

void print_tokens_linked_list(t_token* head) {
    while (head != NULL) {
        printf("%s\n", head->token);
        head = head->next;
    }
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
		while (str[i] != ' ')
			i++;
		add_token(tokens, str, j, i);
	}
	print_tokens_linked_list(tokens);
	free(str);
}
