/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:38:39 by croy              #+#    #+#             */
/*   Updated: 2023/04/24 12:04:17 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
NEED

	strtok
	Fill env to linked list
	Get value from var in linked list
	Set value from var in linked list
 */

// char *ft_strtok(char *str, char *delim);

t_env	*ft_env_new(char *var, char *value)
{
	t_env	*dst;

	dst = malloc(sizeof(t_env));
	if (!dst)
		return (NULL);
	dst->var = var;
	dst->value = value;
	dst->next = NULL;
	return (dst);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

/**
 * @brief gets the envp from a main function and fills a t_env linked list
 * will set the variable in `var` and value in `value`
 *
 * @param envp from a main function where (char **envp)
 * @return t_env* the linked list with every var and its value from the env
 */
t_env	*fill_env(char **envp)
{
	int		i;
	int		j;
	t_env	*ll_env;
	t_env	*current;

	i = -1;
	ll_env = NULL;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j])
		{
			if (envp[i][j] == '=')
			{
				// printf("%c here \n", envp[i][j]);
				printf("\n`%s`\n", envp[i]);
				envp[i][j] = '\0';
				current = ft_env_new(ft_strdup(envp[i]), ft_strdup(envp[i] + j + 1));
				printf("`%s`", current->var);
				printf("`%s`\n", current->value);

				if (!current)
					return (NULL);
					// free memory here
				ft_env_add_back(&ll_env, current);
				break;
			}
			// j++;
		}
		// i++;
	}
	return (ll_env);
}
