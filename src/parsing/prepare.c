#include "minishell.h"

void	prepare_token(t_data *data)
{
	expand_tokens(&data->tokens, data);
	expand_tilde(&data->tokens, data);
	remove_quotes(&data->tokens, data);
	id_tokens(&data->tokens);
	// print_tokens_linked_list(data->tokens);
}
