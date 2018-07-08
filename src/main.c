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
	while (42)
	{
		process(&data);
	}
	return (0);
}

