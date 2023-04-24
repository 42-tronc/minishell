/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:26:14 by croy              #+#    #+#             */
/*   Updated: 2023/04/24 12:45:40 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <limits.h>
# include <unistd.h>

# define RED	"\e[31;1m"
# define RESET	"\e[0m"

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_env	*env;
	t_env	*export;
}			t_data;

// void	ft_cd(char *path, t_list *env);
void	ft_cd(t_env *env, char *path);

void	ft_echo(int ac, char **av);
void	ft_env(t_list *env);
void	ft_export(t_list *env);

// char	*ft_pwd(void);
int		ft_pwd(void);

// Utils for env
t_env	*fill_env(char **envp);
char	*ft_getenv(t_env *ll_env, char *var);
int		ft_setenv(t_env *ll_env, char *var, char *replace);

#endif
