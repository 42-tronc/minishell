/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:13:53 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/05 19:25:37 by arthurasced      ###   ########lyon.fr   */
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
	int	i;
	int	quote;
	int	dquote;
};
// envp.c functions
t_list	*list_env(char **envp);
char	*ft_getenv(t_list *list_envp, char *str);
void	add_env(t_list *list_envp, char *var, char *value);

// parsing.c functions
t_token	*getting_line(t_parsing *data);
void	right_symbols(t_parsing *p, char *str);
void	even_quote(char *str);

// tokens_lst.c functions
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(void *content);

// tokens.c functions
void	cutting_line(t_token **tokens, t_parsing *data, char *str);
void	get_next_word(t_token **tokens, t_parsing *data, char *str);
void	get_symbols(t_token **tokens, t_parsing *p, char *str);
int		get_word_size(t_parsing *data, char *str, int begin);
int		ft_char(int c);

void	print_tokens_linked_list(t_token *head);

#endif
