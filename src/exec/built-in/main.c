#include "minishell.h"

int main(int ac, char *av[], char **envp)
{
	if (ac < 2 || strlen(av[1]) == 0)
	{
		printf("Available functions: echo, cd, env, exit, export, pwd, unset\n");
		return 0;
	}

	t_list	*env;
	env = list_env(envp);

	if (strcmp(av[1], "echo") == 0)
	{
		printf("echo()\n");
		ft_echo(ac, ++av);
	}
	else if (strcmp(av[1], "cd") == 0)
	{
		printf("cd()\n");
		if (ac > 2)
			ft_cd(av[2], env);
		else
			ft_cd(NULL, env);
	}
	else if (strcmp(av[1], "env") == 0)
		printf("env()");
	else if (strcmp(av[1], "exit") == 0)
		printf("exit_func()");
	else if (strcmp(av[1], "export") == 0)
		printf("export()");
	else if (strcmp(av[1], "pwd") == 0)
		printf("pwd()");
	else if (strcmp(av[1], "unset") == 0)
		printf("unset()");
	else
	{
		printf("Invalid function: `%s`\n", av[1]);
		printf("Available functions: echo, cd, env, exit, export, pwd, unset\n");
	}

	return 0;
}

void	ft_echo(int ac, char **av);
void	ft_env(t_list *env);
void	ft_export(t_list *env);
int		ft_pwd(void);
