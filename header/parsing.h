/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:13:53 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/04 13:44:45 by arthurasced      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_token		t_token;
typedef struct s_parsing	t_parsing;

struct s_token {
	char	*token;
	char	*token_id;
	t_token	*next;
};

struct s_parsing {
	int	begin;
	int	end;
	int	quote;
	int	d_quote;
	int	in_word;
};

t_list	*get_envp(char **envp);

t_token	*getting_line(t_parsing *data);
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(void *content);
void	add_token(t_token **tokens, char *str, int begin, int end);

#endif
