/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/04/19 13:27:49 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODO

`-n -n`
	should not display anything

`-nnnn`
	should not display anything

`-n -n Hola`
	`Hola`

`-p`
	`-p`

`Hola -n`
	`Hola -n`

``
	``

`/n hola`
	`n hola`

 */

/**
 * @brief checks if a newline is needed by looking for any '-n' or '-nnnn...'
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
	// printf("NEED NEWLINE CHECKING\n\t`%s`\n", str);
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

void	ft_echo(int ac, char **av)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	// if `-n` then print without \n and skip the `-n`
	if (av[i] && !need_newline(av[i]))
	{
		newline = 0;
		i++;
	}
	// printf("\ti=%d ", i);
	while (av[i] && !need_newline(av[i]))
		i++;
	while (av[i])
	{
		printf("%s", av[i]);
		if (ac - 1 > i)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	// printf("");
	return;
}

/* int	main(int ac, char **av)
{
	ft_echo(ac, av);
	return (0);
} */
