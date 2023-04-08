/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:13:53 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/08 17:45:07 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

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
char	*ft_getenv(t_list *envp, char *str);
int		ft_setenv(t_list *list_envp, char *var, char *value);
void	free_list(t_list *lst);

// parsing.c functions
t_token	*getting_line(t_parsing *data);
void	right_symbols(t_parsing *p, char *str);
void	even_quote(char *str);
void	cutting_line(t_token **tokens, t_parsing *data, char *str);

// tokens_lst.c functions
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(void *content);
void	free_token(t_token *tokens);

// tokens.c functions
void	get_next_word(t_token **tokens, t_parsing *data, char *str, int i);
void	get_symbols(t_token **tokens, t_parsing *p, char *str);
int		get_word_size(t_parsing *data, char *str, int begin);
int		ft_char(int c);
int		ft_char2(int c);

void	print_tokens_linked_list(t_token *head);

#endif
