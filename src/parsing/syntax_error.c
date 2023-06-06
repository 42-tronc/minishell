#include "minishell.h"

int	similar_type(t_token *temp)
{
	int	symbol1;
	int	symbol2;

	symbol1 = 0;
	symbol2 = 0;
	if (!ft_strcmp(temp->type, CHEVRON_L) \
	|| !ft_strcmp(temp->type, CHEVRON_R) \
	|| !ft_strcmp(temp->type, CHEVRON_RR) \
	|| !ft_strcmp(temp->type, PIPE))
		symbol1 = 1;
	if (!ft_strcmp(temp->prev->type, CHEVRON_L) \
	|| !ft_strcmp(temp->prev->type, CHEVRON_R) \
	|| !ft_strcmp(temp->prev->type, CHEVRON_RR) \
	|| !ft_strcmp(temp->prev->type, PIPE))
		symbol2 = 1;
	if (symbol1 && symbol2)
		return (1);
	return (0);
}

int	syntax_error(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (temp->prev)
		{
			if (similar_type(temp))
			{
				printf("minishell: syntax error near unexpected token \
`%s'\n", temp->token);
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}
