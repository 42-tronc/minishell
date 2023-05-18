/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:55:43 by croy              #+#    #+#             */
/*   Updated: 2023/05/18 08:36:23 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "exec.h"
// # include "parsing.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef enum {
	PIPE_ERROR = -3,
	MALLOC_ERROR = -2,
	FAILURE = -1,
	SUCCESS = 0,
}	exit_code;

typedef struct s_env
{
	char			*var;
	char			*value;
	int				in_env;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd_block
{
	int		in_fd;
	int		out_fd;
	char	*heredoc;
}			t_cmd_block;

typedef struct s_token		t_token;

// EXEC
# include <limits.h>
# include <unistd.h>
// include PARSING
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// # define RED	"\e[31;1m"
// # define YELLOW	"\e[33;1m"
// # define GREEN	"\e[32;1m"
// # define UNDERLINE	"\e[4m"
// # define RESET	"\e[0m"

# define BLACK		"\e[30m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define YELLOW		"\e[33m"
# define BLUE		"\e[34m"
# define MAGENTA	"\e[35m"
# define CYAN		"\e[36m"
# define WHITE		"\e[37m"
# define RESET		"\e[0m"

# define BOLD		"\e[1m"
# define NO_BOLD	"\e[22m"
# define UNDERL		"\e[4m"
# define NO_UNDERL	"\e[24m"
# define REVERSED	"\e[7m"
# define ORANGE 	"\e[38;5;208;1m"


# define CHEVRON_L "<"
# define CHEVRON_R ">"
# define INFILE "infile"
# define OUTFILE "outfile"
# define CMD "command"
# define ARG "argument"
# define PIPE "|"
# define LIMITER "limiter"
# define HERE_DOC "here_doc"
# define APPEND "append"
# define MY_NULL "null"

typedef struct s_data		t_data;
typedef struct s_parsing	t_parsing;
typedef struct s_env		t_env;
typedef struct s_token		t_token;

struct s_data {
	t_env		*env;
	t_env		*export; // to remove at one point
	char		**paths;
	int			pipe_count;
	int			i;
	t_parsing	*p;
	t_token		*tokens;
};

struct s_parsing {
	int		i;
	int		quote;
	int		dquote;
	int		all_id;
};

struct s_token {
	char	*token;
	char	*token_id;
	int		pipe_block;
	t_token	*prev;
	t_token	*next;
};

//UTILS
char	**get_array_cmd(t_token *temp);

//EXEC
// void	ft_cd(char *path, t_list *env);
// void	ft_cd(t_env *env, char *path);
// void	ft_cd(t_env *env, t_token *input);
void	ft_cd(t_data *data, t_token *input);

// void	ft_env(t_list *env);
void	ft_env(t_env *env);

// void	ft_export(t_list *env);
void	ft_export(t_env *env, t_list *args);
// void	ft_export(t_env *env);

// void	ft_echo(int ac, char **av);
void	ft_echo(t_token *input);


// char	*ft_pwd(void);
int		ft_pwd(void);

void	ft_unset(t_env **env, t_token *args);
// void	ft_unset(t_env **env, t_list *args);

// Utils for env
t_env	*fill_env(char **envp);
char	*ft_getenv(t_env *env, char *var);
int		ft_addenv(t_env *env, char *var, char *value);
int		ft_setenv(t_env *env, char *var, char *value);

void	print_error(int error_type);

void ft_fork();


void ft_getpaths(t_data *data);
char	**split_paths(char const *s, char c);
// void	get_validpath(t_data *data);
// exit_code	get_validpath(t_data *data);
// char	*get_validpath(t_data *data);
char	*get_validpath(t_data *data, t_token *input);


// void	test_files(t_data *data, char *path);
void	test_files(t_data *data, t_token *input);
char	*ft_strjoin_heredoc(char *s1, char *s2);
void	exec_command(t_data *data, t_token *input);

void	count_pipes(t_data *data);


// PARSING
// envp.c functions
// t_env	*list_env(char **envp);
char	*ft_getenv(t_env *envp, char *str);
int		ft_setenv(t_env *list_envp, char *var, char *value);
void	free_list(t_env *lst);

// envp_lst.c functions
void	ft_envadd_back(t_env **env, t_env *new);
t_env	*ft_envnew(char *name, char *value);

// parsing.c functions
t_token	*getting_line(t_data *data);
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
