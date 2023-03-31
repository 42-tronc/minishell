/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/03/31 12:57:52 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #include "../"

#include <stdio.h>

/* ECHO

X	->	print with \n
-n	->	print without \n
	--n non
 */

int	no_newline(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
	}
	if (!str[i])
		return (1);
	return (0);

}

int	main(void)
{
	printf("cc bg\n");
	if (no_newline())
		printf("loli");
	else
		printf("loli\n");
	return (0);
}
