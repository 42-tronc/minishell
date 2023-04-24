#include "minishell.h"

int main(int ac, char *av[], char **envp)
{
	if (ac < 2 || strlen(av[1]) == 0)
	{
		printf("Available functions: echo, cd, env, exit, export, pwd, unset\n");
		return 0;
	}

	t_env	*env;
	env = fill_env(envp);
	if (strcmp(av[1], "echo") == 0)
	{
		printf("echo()\n\n");
		ft_echo(ac, ++av);
	}
	else if (strcmp(av[1], "cd") == 0)
	{
		printf("cd()\n\n");
		if (ac > 2)
			ft_cd(env, av[2]);
		else
			ft_cd(env, NULL);
		printf("\n ");
		ft_pwd();
	}
	else if (strcmp(av[1], "env") == 0)
	{
		printf("env()\n\n");
		ft_env(env);
	}
	/*
	else if (strcmp(av[1], "exit") == 0)
	{
		printf("exit_func()\n\n");
	}
	else if (strcmp(av[1], "export") == 0)
	{
		printf("export()\n\n");
	}
	else if (strcmp(av[1], "pwd") == 0)
	{
		printf("pwd()\n\n");
	}
	else if (strcmp(av[1], "unset") == 0)
	{
		printf("unset()\n\n");
	}
	*/
	else if (strcmp(av[1], "fill") == 0)
	{
		printf("fill_env()\n\n");
		fill_env(envp);
	}
	else
	{
		printf("Invalid function: `%s`\n", av[1]);
		printf("Available functions: echo, cd, env, exit, export, pwd, unset\n");
	}

	return 0;
}
