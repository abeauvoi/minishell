#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_minishell		data;
	t_env			*list;

	argc = 1;
	argv = NULL;;
	list = set_list(env);
	init_builtin_tab(&data);
	init_error_tab();
	ft_putstr_fd("\033[H\033[2J", 1);
	if (!(env[0]))
		print_error(_ENOENV);
	//init(&g_mini.copy_term);
	//sigtest();
	while (42)
	{
		init_env(&data, list);
		process(&data, &list);
		free_arg(&data.copy_env);
		ft_strdel(&data.pwd);
		free_arg(&data.bin_dirs);
//		ft_strdel(&data.dir);
		free_arg(&data.arg);
	}
	return (0);
}
