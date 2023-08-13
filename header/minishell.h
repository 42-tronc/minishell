/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:55:43 by croy              #+#    #+#             */
/*   Updated: 2023/08/13 10:17:00 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int					g_ret_value;
typedef struct s_data		t_data;
typedef struct s_parsing	t_parsing;
typedef struct s_token		t_token;

typedef enum e_exit_code {
	E_MALLOC = 0,
	E_DUP2 = 1,
	E_PIPE = 2,
	E_FORK = 3,
}	t_exit_code;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd_block
{
	int		is_last;
	int		in_fd;
	int		out_fd;
	int		heredoc_here;
	char	*heredoc;
	int		pipe_fd[2];
	char	*cmd_path;
	char	**cmd_args;
	pid_t	pid;
}			t_cmd_block;

struct s_data {
	t_env		*env;
	t_cmd_block	**cmd_block;
	char		**paths;
	int			cmd_ct;
	int			status;
	int			need_free;
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
	int		to_free;
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
	int		in_quote;
	int		from_expand;
	int		limiter;
	t_token	**head_ref;
	t_token	*prev;
	t_token	*next;
};

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

# define RED		"\e[31m"
# define WHITE		"\e[37m"
# define RESET		"\e[0m"
# define BOLD		"\e[1m"
# define NO_BOLD	"\e[22m"

//	===== @functions =====
// cd.c
int			ft_cd(t_data *data, t_token *input, int block);

// echo.c
int			ft_echo(t_data *data, t_token *input, int block);

// env.c
int			print_env(t_data *data, t_token *input, int block);

// execve.c
char		**get_cmd_args(t_token *input, char *command_path, size_t i);
int			env_size(t_env *env);
char		**env_to_array(t_data *data, t_env *env, int i, char *copy);
int			execve_cmd(t_data *data, t_token *input, int block);

// exit.c
long long	ft_atoll(t_data *data, char *str);
int			ft_exit(t_data *data, t_token *input, int block);

// export.c
int			add_env_entry(t_data *data, t_token *input, int block);
int			ft_export(t_data *data, t_token *input, int block);

// pwd.c
int			ft_pwd(t_data *data, t_token *input, int block);

// unset.c
void		free_env_node(t_env *node);
int			check_var_name(char *var, char *fn);
int			ft_unset(t_data *data, t_token *input, int block);

// split_paths.c
char		**split_paths(char const *s, char c);
void		handle_execve_failure(t_data *data, int block, \
	char *command_path, char **env_array);

// utils_close.c
void		close_fd(int fd);
void		close_parent_fd(t_data *data, int block);
void		close_pipes(t_data *data, int block);

// utils.c
void		print_error(int code, char *source);
void		clean_exit(t_data *data, int code, char *source);
int			count_arguments(t_token *input);
void		swap_var(char **current, char **next);

// utils_env.c
char		*ft_getenv(t_env *env, char *var);
int			ft_setenv(t_data *data, t_env **env, char *var, char *value);

// utils_env2.c
t_env		*ft_env_new(t_data *data, char *var, char *value);
void		ft_env_add_back(t_env **lst, t_env *new);

// utils_execve.c
char		*execve_nopath(t_data *data, t_token *input,
				char **env_array, char *command_path);

// utils_files.c
int			save_here_doc(t_data *data, t_token *input, char *line, int block);
int			check_heredoc(t_data *data, t_token *input, int block);
int			check_infile(t_data *data, t_token *input, int block);
int			check_outfile(t_data *data, t_token *input, int block);

// utils_free.c
void		free_array(char **env_array);
void		free_cmd_block(t_data *data);
void		free_quit(t_data *data);
void		free_in_while(t_data *data);

// utils_heredoc.c
char		*ft_strjoin_heredoc(char *s1, char *s2);

// utils_init.c
void		ft_setenv_mallocd(t_data *data, char *var, char *value, char *malc);
void		fill_env(t_data *data, char **envp);
int			init_data(t_data *data);

// utils_path.c
char		*get_validpath(t_data *data, t_token *input, char **env_array);

// utils_redirections.c
void		check_input(t_data *data, int block);
void		check_output(t_data *data, int block);
int			create_pipe(t_data *data);

// utils_subshell.c
int			check_alone(int (*func)(t_data *, t_token *, int), \
t_data *data, t_token *input, int block);
void		close_all_pipes(t_data *data);
void		ignore_sig(void);
void		create_subshell(int (*func)(t_data *, t_token *, int), \
t_data *data, t_token *input, int block);

// check_in_quotes.c
int			token_in_quotes(char *str);
void		check_in_quotes(t_token **tokens, t_data *data);

// cut_expand.c
void		add_token_in_middle(t_token	*prev, t_token *next, \
char **a, t_data *d);
int			cutting_expand(t_data *data);

// dollar.c
char		*get_var_name(t_data *data, char *str);
char		*get_before_dollar(char *str, t_data *p, int i, int size);
int			replace_var(t_token *temp, t_data *p);
int			expand_tokens(t_token **tokens, t_data *data);
void		join_n_clean(t_token *temp, t_data *p);

// dollar2.c
void		free_expand(t_parsing *p);
int			next_char(char c);
int			processed_line(char *s, t_parsing *p);
int			str_cpy_dollar(char *dst, char *src, int index);
char		*ft_strjoin_dollar(t_data *data, char const *s1, char const *s2);

// dollar3.c
void		exit_dollar(t_data *data, int code, char *source);
void		set_to_null(t_parsing *p);

// envp.c
void		free_list(t_env *lst);

// identification.c
int			is_first_cmd(t_token *head);
void		choose_token_id(t_token *temp);
void		id_tokens(t_token **tokens, t_token *temp);

// parsing.c
int			even_quote(t_parsing *p, char *str);
int			triple_symbol(char *str, int i);
int			right_symbols(t_parsing *p, char *str);
int			getting_line(t_data *data, char *str);

// prepare.c
int			prepare_token(t_data *data);

// replace_list.c
int			need_to_new(t_token *tokens);
int			ft_tokensize(t_token *temp);
int			replace_list(t_data *data, t_token *save, int lst_size);

// rm_quotes.c
int			get_size(t_parsing *p, char *str);
void		copy_without_quotes(char *dst, char *src, t_parsing *p);
int			remove_quotes(t_token **tokens, t_data *data);

// signal.c
void		exit_program(t_data *data);
void		redisplay_prompt(int sig);
void		get_signal_prompt(void);
void		get_signal_exec(void);
void		get_signal_heredoc(void);

// signal2.c
void		handle_signals_heredoc(int signal);
void		handle_sigint(int signal);
void		handle_sigquit(int signal);
void		handle_signals(int signal);

// syntax_error.c
int			similar_type(t_token *temp);
int			check_last_token(t_token *temp);
int			syntax_error(t_data *data);

// tilde.c
int			is_tilde(t_parsing *p, char *str);
void		exit_tilde(t_data *data, int code, char *source, char *copy);
int			replace_tilde(t_token *temp, t_data *data);
int			expand_tilde(t_token **tokens, t_data *data);

// tokens.c
void		exit_parsing(t_data *data, int code, char *source);
int			get_end_token(t_parsing *p, char *str);
char		*copy_str_from_to(t_data *data, int from, int to, char *str);
int			cutting_line(t_data *data, t_token **temp, t_parsing *p, char *str);

// tokens2.c
int			is_symbol(int c);
int			ft_char2(int c);
void		p_quote(t_parsing *p, char c);

// tokens_lst.c
t_token		**find_head_ref(t_token *temp);
void		delete_token(t_token **head_ref, t_token *del);
int			ft_tokenadd_back(t_token **lst, t_token *new);
t_token		*ft_tokennew(void *content);
void		free_token(t_token *tokens);

// minishell.c
void		exec_code(t_data *data);
void		exec_dispatch(t_data *data, t_token *input);

#endif
