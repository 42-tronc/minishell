/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:38:39 by croy              #+#    #+#             */
/*   Updated: 2023/06/13 08:56:32 by croy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief creates a new t_env and dupe the var and value
 *
 * @param var
 * @param value
 * @return t_env* a new t_env node
 */
t_env	*ft_env_new(char *var, char *value)
{
	t_env	*dst;

	dst = malloc(sizeof(t_env));
	if (!dst)
		return (NULL);
	dst->var = NULL;
	dst->value = NULL;
	if (var)
		dst->var = ft_strdup(var);
	if (dst->var && value)
		dst->value = ft_strdup(value);
	if (!dst->var || !dst->value)
	{
		if (!dst->value)
			free(dst->var);
		free(dst);
		return (NULL);
	}
	dst->next = NULL; // Set next to NULL for the new node
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

char	*ft_getenv(t_env *env, char *var)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->var, var) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}


static int	ft_addenv(t_env **env, char *var, char *value)
{
	t_env	*new_entry;

	if (!var)
		return (1);
	new_entry = ft_env_new(var, value);
	if (!new_entry)
		return (2);
	ft_env_add_back(env, new_entry);
	return (0);
}

int	ft_setenv(t_env *env, char *var, char *value)
{
	t_env	*current;

	current = env;
	if (!var)
		return (1);
	while (current)
	{
		if (ft_strcmp(current->var, var) == 0)
		{
			if (!value)
				return (0);
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	return (ft_addenv(&env, var, value));
}

void	print_error(int code)
{
	char	*error[1];

	error[0] = "Malloc failed to allocate a memory space";

	// should prob print to fd 2
	printf(RED"Error: %s\n"RESET, error[code]);
	exit(EXIT_FAILURE);
}

void	create_subshell(void (*func)(t_data*, t_token*, int), t_data *data, t_token *input, int block)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		check_input(data, block); // might not be needed
		check_output(data, block);
		func(data, input, block);
		_exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("Subshell execution complete %d\n", status);
	}
}
