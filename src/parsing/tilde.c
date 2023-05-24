#include "minishell.h"

int	is_tilde(t_parsing *p, char *str)
{
	if (str)
	{
		p_quote(p, str[0]);
		if (str[0] == '~' && !p->quote)
			return (1);
	}
	return (0);
}

void	replace_tilde(t_token *temp, t_data *data)
{
	char	*copy;

	(void)data;
	copy = ft_strdup(temp->token);
	free(temp->token);
	if (copy && (copy[1] == '/' || !copy[1]))
		temp->token = ft_strjoin(ft_getenv(data->env, "HOME"), copy + 1);
	else
		temp->token = ft_strdup(copy);
	free(copy);
}

void	expand_tilde(t_token **tokens, t_data *data)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		if (is_tilde(data->p, temp->token))
			replace_tilde(temp, data);
		temp = temp->next;
	}
}