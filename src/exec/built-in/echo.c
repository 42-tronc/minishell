/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/03/31 16:27:29 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* ECHO

X	->	print with \n
-n	->	print without \n
-nn ->	without \n
--n ->	text
 */

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
	if (str && str[0] == '-')
	{
		if (str && str[1] != 'n')
			return (1);
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] && str[i] != 'n')
			return (1);
	}
	else
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac >= 2)
	{
		printf("Need new line = %d\n", need_newline(av[1]));
		if (need_newline(av[1]))
			printf("loli\n");
		else
			printf("loli");
	}
	printf("pop");
	return (0);
}
