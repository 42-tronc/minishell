/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/03/31 16:11:26 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #include "../"

#include <stdio.h>

/* ECHO

X	->	print with \n
-n	->	print without \n
-nn ->	without \n
--n ->	text
 */

int	need_newline(char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] && str[i] != 'n')
		{
			printf("not an 'n'\n");
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	// if (ac >= 3)
	// {
	// 	printf("cc bg\n");
	// 	// if (need_newline())
	// 		printf("loli");
	// 	else
	// 		printf("loli\n");
	// 	return (0);
	// }
	(void) ac;
	printf("arg = '%s'\n", av[1]);
	printf("Need new line = %d\n", need_newline(av[1]));
	return (0);
}
