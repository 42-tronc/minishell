/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <aascedu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:19:54 by arthurasced       #+#    #+#             */
/*   Updated: 2023/04/06 10:03:46 by aascedu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens_linked_list(t_token *head)
{
	t_token	*temp;
	int		i;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		printf("token[%d]___%s___\n", i++, temp->token);
		temp = temp->next;
	}
}

void	print_list(t_list *head)
{
	t_list	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

void	even_quote(char *str)
{
	int	i;
	int	nb_quote;
	int	nb_dquote;

	nb_quote = 0;
	nb_dquote = 0;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			nb_quote++;
		if (str[i] == '\"')
			nb_dquote++;
	}
	if (nb_quote % 2 != 0 || nb_dquote % 2 != 0)
	{
		free(str);
		printf("error - quotes or double quotes not closed correctly\n");
		exit (1);
	}
}

void	right_symbols(t_parsing *p, char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		p->quote = (p->quote + (!p->dquote && str[i] == '\'')) % 2;
		p->dquote = (p->dquote + (!p->quote && str[i] == '\"')) % 2;
		if (i >= 1 && p->quote == 0 && p->dquote == 0)
		{
			if (str[i] == '|' && str[i - 1] == '|')
			{
				printf ("error ||\n");
				exit (1);
			}
		}
		if (i >= 2 && p->quote == 0 && p->dquote == 0)
		{
			if ((str[i] == '>' && str[i - 1] == '>' && str[i - 2] == '>')
				|| (str[i] == '<' && str[i - 1] == '<' && str[i - 2] == '<'))
			{
				printf ("error <<< or >>>\n");
				exit (1);
			}
		}
	}
}

t_token	*getting_line(t_parsing *p)
{
	t_token	*tokens;
	char	*str;

	tokens = NULL;
	str = readline("minishell>");
	p->i = 0;
	p->quote = 0;
	p->dquote = 0;
	even_quote(str);
	right_symbols(p, str);
	cutting_line(&tokens, p, str);
	return (free(str), tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*tokens;
	t_list		*env;
	t_parsing	p;

	tokens = getting_line(&p);
	print_tokens_linked_list(tokens);
	free_token(tokens);
	(void)argc;
	(void)argv;
	env = list_env(envp);
	add_env(env, "HOME=", "test");
	//print_list(env);
	free_list(env);
	return (0);
}
