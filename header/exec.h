/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:26:14 by croy              #+#    #+#             */
/*   Updated: 2023/04/18 11:00:19 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <limits.h>
# include <unistd.h>

# define RED	"\e[31;1m"
# define RESET	"\e[0m"

// char	*ft_pwd(void);
int		ft_pwd(void);
void	ft_env(t_list *env);

#endif
