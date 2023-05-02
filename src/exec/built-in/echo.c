/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/05/02 17:35:25 by croy             ###   ########lyon.fr   */
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

/**
 * @brief print a string or an array of strings
 *
 * @param ac nb of args passed
 * @param av array of args to print
 */
void	ft_echo(t_token *input)
{
	int	newline;

	printf(YELLOW"ft_echo()\n"RESET);
	newline = 1;
	input = input->next;
	if (input->token && !need_newline(input->token))
	{
		newline = 0;
		input = input->next;
	}
	while (input->token && !need_newline(input->token))
		input = input->next;

	while (input)
	{
		printf("%s", input->token);
		if (input->next)
			printf(" ");
		input = input->next;
	}
	if (newline)
		printf("\n");
	return;
}

/* loli */
