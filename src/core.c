#include "minishell.h"
#include <stdio.h>

void	print_prompt(t_minishell *data)
{
	ft_putstr("\x1B[1;33m");
	ft_putstr("| ");
	ft_putstr("\x1B[1;36m");
	ft_putstr(data->dir);
	ft_putstr("\x1B[1;33m");
	ft_putstr(" | ");
	ft_putstr("\x1B[1;32m");
	ft_putstr("$> ");
	ft_putstr("\x1B[0;0m");
}

void	get_fork(t_minishell *data)
{
	pid_t	father;

	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
	{
		execve(data->valide_path, data->arg, data->copy_env);
		exit(0);
	}
}

void	process(t_minishell *data)
{
	char *line;

	print_prompt(data);
	while (get_next_line(1, &line) != 2);
	data->arg = ft_strsplit(line, ' ');
	if (data->arg[0] != NULL)
		if (ft_strncmp(data->arg[0], "exit", 4) == 0)
			exit(EXIT_SUCCESS);
	data->valide_path = check_path(data);
	get_fork(data);
}
