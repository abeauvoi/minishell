#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_minishell *data;
	int			i;

	i = 0;
	argc = 1;
	argv = NULL;
	if (!(data = malloc(sizeof(t_minishell))))
		return (-1);
	get_env(env, data);
	while (42)
	{
		process(data);
	}
	return (0);
}

