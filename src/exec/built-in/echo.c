/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/04/03 12:43:35 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/**
 * @brief checks if a newline is needed by looking for any '-n'
 *
 * @param str string to check
 * @return int 1 if needed, 0 if not
 */
int	need_newline(char *str)
{
	int	i;

	i = 1;
	// if (!str)
	// 	return (1);
	if (str && str[0] == '-')
	{
		if (str && str[1] == 'n')
		{
			i++;
			while (str[i] && str[i] == 'n')
				i++;
			if (!str[i])
				return (0);
		}
	}
	return (1);
}

/* int	main(int ac, char **av)
{
	if (ac >= 2)
	{
		printf("param= '%s'\n", av[1]);
		printf("Need new line = %d\n", need_newline(av[1]));
		if (need_newline(av[1]))
			printf("loli\n");
		else
			printf("loli");
	}
	printf("pop");
	return (0);
} */
