#include "minishell.h"

int	get_size(t_parsing *p, char *str)
{
	int	i;
	int	size;

	i = 0;
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
	while (src && src[i_src])
	{
		p_quote(p, src[i_src]);
		printf("\':%d, \":%d et ", p->quote, p->dquote);
		if (src[i_src] != '\'' && src[i_src] != '\"')
		{
			dst[++i_dst] = src[i_src];
		}
		else if (src[i_src] == '\'' && p->dquote)
		{
			printf("duvweioubv\n");
			dst[++i_dst] = src[i_src];
		}
		else if (src[i_src] == '\"' && p->quote)
		{
			printf("HJERE\n");
			dst[++i_dst] = src[i_src];
		}
		printf("%c   %c\n", src[i_src], dst[i_dst]);
		i_src++;
	}
	dst[++i_dst] = '\0';
}

void	remove_quotes(t_token **tokens, t_data *data)
{
	t_token	*temp;
	char	*new;

	temp = *tokens;
	while (temp)
	{
		data->p->quote = 0;
		data->p->dquote = 0;
		new = malloc(sizeof(char) * (get_size(data->p, temp->token) + 1));
		if (!new)
			return ;
		data->p->quote = 0;
		data->p->dquote = 0;
		copy_without_quotes(new, temp->token, data->p);
		free(temp->token);
		temp->token = ft_strdup(new);
		free(new);
		temp = temp->next;
	}
}