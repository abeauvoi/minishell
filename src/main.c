#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_minishell *data;

	argc = 1;
	argv = NULL;
	if (!(data = malloc(sizeof(t_minishell))))
		return (-1);
	get_env(env, data);
	ft_putstr(data->pwd);
	return (0);
}

