/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:08:49 by croy              #+#    #+#             */
/*   Updated: 2023/06/19 14:45:25 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static long long	convert_digits(const char *str, int *i, int sign)
{
	int			digit;
	long long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (is_overflow(result, digit * sign))
		{
			ft_putendl_fd("exit error: overflow during number conversion.", 2);
			exit(2);
		}
		result = result * 10 + digit * sign;
		(*i)++;
	}
	return (result);
}

long long	ft_atoll(const char *str)
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
	result = convert_digits(str, &i, sign);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i])
	{
		ft_putendl_fd("exit error: numeric argument required.", 2);
		exit(2);
	}
	return (result);
}

void	ft_exit(t_data *data, t_token *input)
{
	char	*token;
	int		exit_code;

	free(data->p);
	free(data->cmd_block);
	if (!input)
		exit(0);
	token = input->token;
	exit_code = ft_atoll(token);
	printf("error code %d\n", exit_code);
	while (exit_code < 0)
		exit_code = exit_code + 256;
	exit(exit_code % 256);
}
