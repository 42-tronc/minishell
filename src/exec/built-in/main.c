#include "minishell.h"

t_list	*ft_av_to_list(int ac, char **av)
{
	int		i;
	t_list	*arg_list;

	i = 2;
	arg_list = NULL;
	while (i < ac)
		ft_lstadd_back(&arg_list, ft_lstnew(av[i++]));
	return (arg_list);
}

int main(int ac, char *av[], char **envp)
{
	t_env	*env;
	t_list	*args;

	if (ac < 2 || ft_strlen(av[1]) == 0)
	{
		printf("Available functions: echo, cd, env, exit, export, pwd, unset\n");
		return 0;
	}

	env = fill_env(envp);
	args = ft_av_to_list(ac, av);
	if (ft_strcmp(av[1], "echo") == 0)
	{
		printf("echo()\n\n");
		ft_echo(ac, ++av);
	}
	else if (ft_strcmp(av[1], "cd") == 0)
	{
		printf("cd()\n\n");
		if (ac > 2)
			ft_cd(env, av[2]);
		else
			ft_cd(env, NULL);
		printf("\n ");
		ft_pwd();
	}
	else if (ft_strcmp(av[1], "env") == 0)
	{
		printf("env()\n\n");
		ft_env(env);
	}
	else if (ft_strcmp(av[1], "exit") == 0)
	{
		printf("exit()\n\n");
	}
	else if (ft_strcmp(av[1], "export") == 0)
	{
		printf("export()\n\n");
		ft_export(env, args);
	}
	else if (ft_strcmp(av[1], "pwd") == 0)
	{
		printf("pwd()\n\n");
	}
	else if (ft_strcmp(av[1], "unset") == 0)
	{
		printf("unset()\n\n");
		ft_unset(&env, args);
		ft_env(env);
	}
	else if (ft_strcmp(av[1], "fork") == 0)
	{
		printf("fork()\n\n");
		ft_fork();
	}
	else
	{
		printf("Invalid function: `%s`\n", av[1]);
		printf("Available functions: echo, cd, env, exit, export, pwd, unset\n");
	}

	return 0;
}
