/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:31:40 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/04 14:04:12 by arthurasced      ###   ########lyon.fr   */
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
		dst->token_id = NULL;
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

static void	even_quote(char *str)
{
	int	i;
	int	nb_quote;
	int	nb_dquote;

	nb_quote = 0;
	nb_dquote = 0;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			nb_quote++;
		if (str[i] == '\"')
			nb_dquote++;
	}
	if (nb_quote % 2 != 0 || nb_dquote % 2 != 0)
	{
		free(str);
		printf("error - quotes or double quotes not closed correctly\n");
		exit (1);
	}
}

static void	get_next_word(t_token **tokens, t_parsing *data, char *str)
{
	while (str && str[data->end])
	{
		
	}
}

static void	cutting_line(t_token **tokens, t_parsing *data, char *str)
{
	while (str && str[data->end])
	{
		data->begin = data->end;
		if (str[data->end] == ' ')
			data->end++;
		else if (str[data->end] == '\'' || str[data->end] == '\"'
			|| ft_isalpha(str[data->end]))
			return ;
			// get_next_word(tokens, data, str);
		// if (str[data->end] == '\'')
		// 	till_next_quote(tokens, data, str);
		// if (ft_isalpha(str[data->end]))
	}
}

t_token	*getting_line(t_parsing *data)
{
	t_token	*tokens;
	char	*str;

	(void)data;
	tokens = NULL;
	str = readline("minishell>");
	even_quote(str);
	cutting_line(&tokens, data, str);
	return (free(str), tokens);
}

		data->begin = data->end;
		while (str[data->end] != ' ' && str[data->end])
			data->end++;
		add_token(&tokens, str, data->begin, data->end);
		while (str[data->end] == ' ' && str[data->end])
			data->end++;