/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aascedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:57:47 by aascedu           #+#    #+#             */
/*   Updated: 2023/06/23 11:26:23 by aascedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size(t_parsing *p, char *str)
{
	int	i;
	int	size;

	i = 0;
	p->dquote = 0;
	p->quote = 0;
	size = 0;
	while (str && str[i])
	{
		p_quote(p, str[i]);
		if (str[i] != '\'' && str[i] != '\"')
			size++;
		else if (str[i] == '\'' && p->dquote)
			size++;
		else if (str[i] == '\"' && p->quote)
			size++;
		i++;
	}
	return (size);
}

void	copy_without_quotes(char *dst, char *src, t_parsing *p)
{
	int	i_dst;
	int	i_src;

	i_dst = -1;
	i_src = 0;
	p->quote = 0;
	p->dquote = 0;
	while (src && src[i_src])
	{
		p_quote(p, src[i_src]);
		if (src[i_src] != '\'' && src[i_src] != '\"')
			dst[++i_dst] = src[i_src];
		else if (src[i_src] == '\'' && p->dquote)
			dst[++i_dst] = src[i_src];
		else if (src[i_src] == '\"' && p->quote)
			dst[++i_dst] = src[i_src];
		i_src++;
	}
	dst[++i_dst] = '\0';
}

int	remove_quotes(t_token **tokens, t_data *data)
{
	t_token	*temp;
	char	*new;

	temp = *tokens;
	while (temp)
	{
		if (temp->in_quote)
		{
			new = malloc(sizeof(char) * (get_size(data->p, temp->token) + 1));
			if (!new)
				exit_parsing(data, E_MALLOC, "remove_quotes");
			copy_without_quotes(new, temp->token, data->p);
			if (ft_strcmp(temp->token, new))
				temp->in_quote = 1;
			free(temp->token);
			temp->token = ft_strdup(new);
			if (!temp->token)
				exit_tilde(data, E_MALLOC, "remove_quotes", new);
			free(new);
		}
		temp = temp->next;
	}
	return (0);
}
