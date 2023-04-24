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

	// t_env	*env;
	// env = fill_env(envp);
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
	{
		printf("env()\n");
		ft_env(env);
	}
	else if (strcmp(av[1], "exit") == 0)
	{
		printf("exit_func()\n");
	}
	else if (strcmp(av[1], "export") == 0)
	{
		printf("export()\n");
	}
	else if (strcmp(av[1], "pwd") == 0)
	{
		printf("pwd()\n");
	}
	else if (strcmp(av[1], "unset") == 0)
	{
		printf("unset()\n");
	}
	else if (strcmp(av[1], "fill") == 0)
	{
		printf("fill_env()\n");
		fill_env(envp);
	}
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
