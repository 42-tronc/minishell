/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:26:14 by croy              #+#    #+#             */
/*   Updated: 2023/04/20 13:56:08 by croy             ###   ########lyon.fr   */
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

// char	*ft_pwd(void);
void	ft_cd(char *path, t_list *env);
void	ft_echo(int ac, char **av);
void	ft_env(t_list *env);
void	ft_export(t_list *env);
int		ft_pwd(void);

void	fill_env(char **envp);

#endif
