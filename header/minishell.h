/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:55:43 by croy              #+#    #+#             */
/*   Updated: 2023/05/02 16:46:18 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
// # include "exec.h"
// # include "parsing.h"
# include <stdio.h>

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token		t_token;

// EXEC
# include <limits.h>
# include <unistd.h>

# define RED	"\e[31;1m"
# define ORANGE "\e[38;5;208;1m"
# define YELLOW	"\e[33;1m"
# define RESET	"\e[0m"

typedef struct s_data
{
	t_env	*env;
	t_env	*export;
	int		i;
}			t_data;

// void	ft_cd(char *path, t_list *env);
void	ft_cd(t_env *env, char *path);

// void	ft_env(t_list *env);
void	ft_env(t_env *env);

// void	ft_export(t_list *env);
void	ft_export(t_env *env, t_list *args);
// void	ft_export(t_env *env);

// void	ft_echo(int ac, char **av);
void	ft_echo(t_token *input);


// char	*ft_pwd(void);
int		ft_pwd(void);

void	ft_unset(t_env **env, t_list *args);

// Utils for env
t_env	*fill_env(char **envp);
char	*ft_getenv(t_env *env, char *var);
int		ft_addenv(t_env *env, char *var, char *value);
int		ft_setenv(t_env *env, char *var, char *value);

void	print_error(int error_type);

void ft_fork();



// PARSING
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CHEVRON_L "<"
# define CHEVRON_R ">"
# define INFILE "infile"
# define OUTFILE "outfile"
# define CMD "command"
# define ARG "argument"
# define PIPE "|"
# define LIMITER "limiter"
# define HERE_DOC "here_doc"
# define HERE_DOC_END "here_doc_end"
# define MY_NULL "null"

typedef struct s_parsing	t_parsing;

struct s_token {
	char	*token;
	char	*token_id;
	int		pipe_block;
	t_token	*prev;
	t_token	*next;
};

struct s_parsing {
	int		i;
	int		quote;
	int		dquote;
	int		all_id;
	t_env	*env;

};

// envp.c functions
// t_env	*list_env(char **envp);
char	*ft_getenv(t_env *envp, char *str);
int		ft_setenv(t_env *list_envp, char *var, char *value);
void	free_list(t_env *lst);
// char	*ft_strndup(char *str, int stop);

// envp_lst.c functions
void	ft_envadd_back(t_env **env, t_env *new);
t_env	*ft_envnew(char *name, char *value);

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
void	get_symbols(t_token **tokens, t_parsing *p, char *str, int size);
int		get_word_size(t_parsing *data, char *str, int begin);

// tokens2.c functions
int		ft_char(int c);
int		ft_char2(int c);
void	p_quote(t_parsing *p, char c);
int		is_symbol(int c);

// dollar.c functions
void	expand_tokens(t_token **tokens, t_data *data);
void	replace_var(t_token *temp, t_data *p);
char	*get_before_dollar(char *str, t_data *p);
char	*get_var_name(char *str);

// dollar2.c functions
char	*ft_strjoin_dollar(char const *s1, char const *s2);
int		str_cpy_dollar(char *dst, char *src, int index);
int		processed_line(char *str);
int		next_char(char c);

// identification.c functions
void	id_tokens(t_token **tokens);
void	command_arg_file(t_token *temp);
int		first_token(t_token *temp);

// identification2.c functions
int		is_separator(t_token *temp);
int		first_token(t_token *temp);

void	print_tokens_linked_list(t_token *head);



#endif
