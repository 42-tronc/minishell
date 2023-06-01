/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:08:49 by croy              #+#    #+#             */
/*   Updated: 2023/06/01 12:43:03 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
NEED

free everything then exit with proper exit code
check if nb
need to divide something by something to get real exit code
 */
#include "minishell.h"

// static free_everything()
// will need a function to free any var before exiting

static int	is_overflow(long long result, int digit)
{
	if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
			&& digit > LLONG_MAX % 10))
		return (1);
	else if (result < LLONG_MIN / 10 || (result == LLONG_MIN / 10
			&& digit < LLONG_MIN % 10))
		return (1);
	return (0);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	int			digit;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	// Skip leading whitespace and check for sign
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	// Convert digits
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (is_overflow(result, digit * sign))
		{
			printf("Overflow occurred during conversion.\n");
			exit(2);
		}
		result = result * 10 + digit * sign;
		// printf("result = %lld\n", result);
		i++;
	}
	// Skip trailing whitespace (like `exit 5  `)
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	// Check if the string is done (if not that's a pb)
	if (str[i] != '\0')
	{
		printf("Invalid number format.\n");
		exit(2);
	}
	return (result);
}

void	ft_exit(t_token *input)
{
	int		i;
	char	*token;
	int		exit_code;

	if (!input)
		exit(0);
	// Check if the input string is a valid number
	i = 0;
	token = input->token;
	while (token[i])
	{
		if ((token[i] < '0' || token[i] > '9') && !(i == 0 && (token[i] == '+'
					|| token[i] == '-')))
		{
			printf("exit: numeric argument required\n");
			exit(2);
		}
		i++;
	}
	exit_code = ft_atoll(token);
	printf("error code %d\n", exit_code);
	while (exit_code < 0)
		exit_code = exit_code + 256;
	// exit_code = exit_code ;
	exit(exit_code % 256 );
}
