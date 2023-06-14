/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:55:43 by croy              #+#    #+#             */
/*   Updated: 2023/06/13 12:59:49 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "exec.h"
// # include "parsing.h"
# include "libft.h"
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data		t_data;
typedef struct s_parsing	t_parsing;
// typedef struct s_env		t_env;
typedef struct s_token		t_token;

typedef enum e_exit_code {
	PIPE_ERROR = -3,
	MALLOC_ERROR = -2,
	FAILURE = -1,
	SUCCESS = 0,
}	t_exit_code;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd_block
{
	int		in_fd;
	int		out_fd;
	char	*heredoc;
	int		pipe_fd[2];
	char	*cmd_path; // MIGHT NOT BE NEEDED
	char	**cmd_args; // MIGHT NOT BE NEEDED
	// int		*pipin;
	// int		*pipout;
}			t_cmd_block;

struct s_data {
	t_env		*env;
	char		**og_env;
	t_env		*export; // to remove at one point
	t_cmd_block	**cmd_block;
	char		**paths;
	int			cmd_block_count;
	int			i;
	t_parsing	*p;
	t_token		*tokens;
};

struct s_parsing {
	int		i;
	int		start;
	int		quote;
	int		dquote;
	int		all_id;
	char	*before;
	char	*var_value;
	char	*before_and_value;
	char	*new_token;
	char	*var_name;
};

struct s_token {
	char	*token;
	char	*type;
	int		pipe_block;
	t_token	*prev;
	t_token	*next;
};

// define for token_id.
# define CHEVRON_L "<"
# define CHEVRON_R ">"
# define INFILE "infile"
# define OUTFILE "outfile"
# define APPEND "append"
# define CMD "command"
# define ARG "argument"
# define PIPE "|"
# define LIMITER "limiter"
# define HERE_DOC "here_doc"
# define CHEVRON_RR ">>"
# define MY_NULL "my_null"

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

//	===== @functions =====
// cd.c
void		ft_cd(t_data *data, t_token *input);

// echo.c
int			check_newline(t_token **input);
void		echo_print(t_data *data, t_token *input, int block);
void		ft_echo(t_data *data, t_token *input, int block);

// env.c
void	print_env(t_data *data, t_token *input, int block);
void	ft_env(t_data *data, t_token *input, int block);
t_env	*fill_env(char **envp);

// exit.c
long	long	ft_atoll(const char *str);
void	ft_exit(t_token *input);

// export.c
void		add_env_entry(t_env *env, t_token *input, int block);
void		ft_export(t_data *data, t_token *input, int block);

// pwd.c
int			ft_pwd(void);

// unset.c
void		ft_unset(t_env **env, t_token *args);

// utils.c
t_env	*ft_env_new(char *var, char *value);
void	ft_env_add_back(t_env **lst, t_env *new);
char	*ft_getenv(t_env *env, char *var);
int	ft_setenv(t_env *env, char *var, char *value);
void	print_error(int code);
void	create_subshell(void (*func)(t_data*, t_token*, int), t_data *data, t_token *input, int block);

// execve.c
int	ft_getpaths(t_data *data);
char	*get_validpath(t_data *data, t_token *input);
char	**get_cmd_args(t_token *input, char *command_path);
int	check_output(t_data *data, int block, char *cmd_path);
int	check_input(t_data *data, int block, char *cmd_path);
int	create_pipe(t_data *data);
void	exec_command(t_data *data, t_token *input, int block);

// files.c
void		check_heredoc(t_data *data, t_token *input, int block);
int			check_infile(t_data *data, t_token *input, int block);
int			check_outfile(t_data *data, t_token *input, int block);

// fork.c
void		ft_fork(void);

// strjoin_heredoc.c
char		*ft_strjoin_heredoc(char *s1, char *s2);

// dollar.c
char		*get_var_name(char *str);
char		*get_before_dollar(char *str, t_data *p, int i, int size);
void		free_expand(t_parsing *p);
int			replace_var(t_token *temp, t_data *p);
int			expand_tokens(t_token **tokens, t_data *data);

// dollar2.c
int			next_char(char c);
int			processed_line(char *str, t_parsing *p);
int			str_cpy_dollar(char *dst, char *src, int index);
char		*ft_strjoin_dollar(char const *s1, char const *s2);

// envp.c
void		free_list(t_env *lst);

// envp_lst.c
void		ft_envadd_back(t_env **env, t_env *new);
t_env		*ft_envnew(char *var, char *value);

// identification.c
int			is_first_cmd(t_token *head);
void		choose_token_id(t_token *temp);
void		id_tokens(t_token **tokens, t_token *temp);

// parsing.c
int			even_quote(t_parsing *p, char *str);
int			triple_symbol(char *str, int i);
int			right_symbols(t_parsing *p, char *str);
int			getting_line(t_data *data);

// prepare.c
int			prepare_token(t_data *data);

// rm_quotes.c
int			get_size(t_parsing *p, char *str);
void		copy_without_quotes(char *dst, char *src, t_parsing *p);
int			remove_quotes(t_token **tokens, t_data *data);

// signal.c
void		exit_program(t_data *data);
void		redisplay_prompt(int sig);
void		get_signal(void);

// syntax_error.c
int			similar_type(t_token *temp);
int			check_last_token(t_token *temp);
int			syntax_error(t_data *data);

// tilde.c
int			is_tilde(t_parsing *p, char *str);
int			replace_tilde(t_token *temp, t_data *data);
int			expand_tilde(t_token **tokens, t_data *data);

// tokens.c
int			get_end_token(t_parsing *p, char *str);
char		*copy_str_from_to(int from, int to, char *str);
int			cutting_line(t_token **temp, t_parsing *p, char *str);

// tokens2.c
int			is_symbol(int c);
int			ft_char2(int c);
void		p_quote(t_parsing *p, char c);

// tokens_lst.c
int			ft_tokenadd_back(t_token **lst, t_token *new);
t_token		*ft_tokennew(void *content);
void		free_token(t_token *tokens);

// exec_char.c
char		**get_array_cmd(t_token *temp);

// minishell.c
void		print_tokens_linked_list(t_token *head);
void		check_command(t_data *data, t_token *input, int block);
void		exec_dispatch(t_data *data, t_token *input);
int			init_data(t_data *data);

// split_paths.c
char		**split_paths(char const *s, char c);

#endif
