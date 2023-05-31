/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:41:40 by croy              #+#    #+#             */
/*   Updated: 2023/05/31 08:15:04 by croy             ###   ########lyon.fr   */
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
 * @return int 1 if needed so no `-n` found, else 0
 */
static int	need_newline(char *str)
{
	int	i;

	i = 1;
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
	int	first;
	int	newline;

	first = 1;
	newline = 1;
	// if there is a `-n`, set the newline to 0
	if (input && input->token && !need_newline(input->token))
	{
		newline = 0;
		input = input->next;
	}
	// if there is a `-n`, skip every -n
	while (input && input->token && !need_newline(input->token))
		input = input->next;
	// only print arguments
	while (input && ft_strcmp(input->type, PIPE) != 0)
	{
		if (ft_strcmp(input->type, ARG) == 0)
		{
			printf("%s", input->token);
			first = 0;
		}
		if (input->next && ft_strcmp(input->next->type, ARG) == 0 && !first)
			printf(" ");
		input = input->next;
	}
	// printf("`");
	if (newline)
		printf("\n");
}
