#include "minishell.h"

void    handle_sigint(int signal)
{
    (void)signal;
    g_ret_value = 130;
    printf("\n");
}

void    handle_sigquit(int signal)
{
    (void)signal;
    g_ret_value = 131;
    printf("Quit (core dumped)\n");
}
