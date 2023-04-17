/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:08:49 by croy              #+#    #+#             */
/*   Updated: 2023/04/05 17:48:09 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
NEED

free everything then exit with proper exit code
need to divide something by something to get real exit code
 */
int	ft_exit(int code);
{
	return (exit(code), code);
}
