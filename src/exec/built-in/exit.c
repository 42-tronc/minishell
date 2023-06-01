/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:08:49 by croy              #+#    #+#             */
/*   Updated: 2023/06/01 11:44:00 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
NEED

free everything then exit with proper exit code
check if nb
need to divide something by something to get real exit code
 */
#include "minishell.h"

static int	is_int(long long number)
{
	return (number >= LONG_MIN && number <= 9223372036854775807);
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	// skip leading whitespace
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	// check for sign
	if (str[i] == '+' || str[i] == '-')
		i++;
	// check for digits
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}
	// skip trailing whitespace
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	// check if the string is terminated
	printf("is valid number %d\n", !str[i]);
	return (str[i] == '\0');
}

void	ft_exit(t_token *input)
{
	long long	exit_code;

	if (!input)
		exit(0);
	// checkString(input->token, 0, 0, 1);
	if (is_valid_number(input->token))
	{
		exit_code = atoll(input->token);
		printf("error code %lld\n", exit_code);
		if (!is_int(exit_code))
		{
			printf("exit: numeric argument required\n");
			exit(2);
		}
		while (exit_code < 0)
			exit_code = exit_code + 256;
		exit_code = exit_code % 256;
		exit(exit_code);
	}
	else
	{
		printf("exit: numeric argument required\n");
		exit(2);
	}
}
