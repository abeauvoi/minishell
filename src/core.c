#include "minishell.h"
#include <stdio.h>

void	free_arg(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		ft_strdel(&arg[i]);
		i++;
	}
	free(arg);
}

static void	print_prompt(t_minishell *data)
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

	(void)data;
	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
	{
		execve(data->valide_path, data->arg, data->copy_env);
		ft_strdel(&data->valide_path);
		exit(0);
	}
}

void	process(t_minishell *data, t_env **list)
{
	char	*line;
	int		i;

	i = 0;
	print_prompt(data);
	while (get_next_line(1, &line) != 2);
	data->arg = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (!data->arg[0])
		return ;
	if ((i = check_builtin(data)) >= 0)
		exec_builtin(data, i, list);
	else
	{
		if ((data->valide_path = check_access(data)) == NULL)
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(data->arg[0]);
			return ;
		}
		get_fork(data);
	}
}
