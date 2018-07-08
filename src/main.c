#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_minishell data;

	argc = 1;
	argv = NULL;
	get_env(env, &data);
	data.copy_env = env;
	ft_putstr_fd("\033[H\033[2J", 1);
	if (!(env[0]))
	{
		ft_putendl_fd("error : env is missing", 2);
		exit(EXIT_FAILURE);
	}
	while (42)
	{
		process(&data);
	}
	return (0);
}
