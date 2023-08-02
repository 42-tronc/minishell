/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:00:46 by croy              #+#    #+#             */
/*   Updated: 2023/08/02 12:25:43 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, t_token *input, int block)
{
	char	cwd[BUFSIZ];

	(void)data;
	(void)input;
	(void)block;
	if (getcwd(cwd, BUFSIZ))
		printf("%s\n", cwd);
	else
		return (perror(BOLD RED "pwd" RESET), 1);
	return (0);
}
