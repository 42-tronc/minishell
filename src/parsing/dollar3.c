#include "minishell.h"

void	exit_dollar(t_data *data, int code, char *source)
{
	free_expand(data->p);
	free_token(data->tokens);
	free_list(data->env);
	free(data->p);
	free(data);
	print_error(code, source);
	rl_clear_history();
	exit (1);
}

void	set_to_null(t_parsing *p)
{
	p->to_free = 0;
	p->before = NULL;
	p->var_name = NULL;
	p->var_value = NULL;
	p->before_and_value = NULL;
	p->new_token = NULL;
}
