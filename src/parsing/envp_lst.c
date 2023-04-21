/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:08:10 by aascedu           #+#    #+#             */
/*   Updated: 2023/04/21 14:08:12 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*temp;

	if (!env)
		return ;
	if (!*env)
		*env = new;
	else
	{
		temp = *env;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_env	*ft_envnew(char *name, char *value)
{
	t_env	*dst;

	dst = malloc(sizeof(t_env));
	if (!dst)
		return (NULL);
	dst->name = name;
	dst->value = value;
	dst->next = NULL;
	return (dst);
}
