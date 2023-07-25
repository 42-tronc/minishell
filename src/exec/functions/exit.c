/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:08:49 by croy              #+#    #+#             */
/*   Updated: 2023/06/26 13:51:38 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if the result of the conversion is an overflow
 *
 * @param result int to check for overflow
 * @param digit single digit to check for overflow
 * @return int 1 if overflow, 0 if not
 */
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

/**
 * @brief converts the digits of the string to a long long
 *
 * @param str string to convert
 * @param i index of the string to start the conversion from
 * @param sign of the number
 * @return long long converted number
 */
static long long	convert_digits(t_data *data, char *str, int *i, int sign)
{
	int			digit;
	long long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (is_overflow(result, digit * sign))
		{
			ft_putendl_fd("exit error: numeric argument required", 2);
			free_quit(data);
			exit(2);
		}
		result = result * 10 + digit * sign;
		(*i)++;
	}
	return (result);
}

/**
 * @brief converts a string to a long long
 *
 * @param str string to convert
 * @return long long converted number
 */
long long	ft_atoll(t_data *data, char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = convert_digits(data, str, &i, sign);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i])
	{
		ft_putendl_fd("exit error: numeric argument required", 2);
		free_quit(data);
		exit(2);
	}
	return (result);
}

/**
 * @brief exits the shell
 *
 * @param data t_data struct with status and vars to free
 * @param input t_token struct to check for args
 * @param block void in this case
 * @return int EXIT_SUCCESS or EXIT_FAILURE
 */
int	ft_exit(t_data *data, t_token *input, int block)
{
	int		exit_code;

	(void)block;
	exit_code = 0;
	if (!input)
	{
		free_quit(data);
		exit(0);
	}
	if (count_arguments(input) > 1)
	{
		ft_putendl_fd("exit error: too many arguments", 2);
		g_ret_value = 1;
		free_quit(data);
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(input->type, ARG) == 0)
		exit_code = ft_atoll(data, input->token);
	while (exit_code < 0)
		exit_code = exit_code + 256;
	free_quit(data);
	exit(exit_code % 256);
	return (EXIT_SUCCESS);
}
