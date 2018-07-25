#include <stdio.h>
#include "minishell.h"

void	free_arg(char ***arg)
{
	char	**cpy;

	cpy = *arg;
	if (*arg == NULL)
		return ;
	while (*cpy)
		ft_strdel(cpy++);
	free(*arg);
	(*arg) = NULL;
}

static void	print_prompt(t_env *list)
{
	char	*pwd;
	char	*home;
	size_t	len_home;

	ft_putstr("\x1B[1;33m");
	ft_putstr("| ");
	ft_putstr("\x1B[1;36m");
	if ((pwd = ft_getenv(list, "PWD=", 4)) != NULL)
	{
		if ((home = ft_getenv(list, "HOME=", 5)) != NULL)
		{
			len_home = ft_strlen(home);
			if (home[len_home - 1] == '/')
				--len_home;
		}
		if (home && ft_strncmp(pwd, home, (home ? len_home : 0)) == 0)
		{
			pwd += len_home;
			ft_putchar('~');
			if (pwd[0] == '/' && pwd[1] != '\0')
				ft_putstr(pwd);
		}
		else
			ft_putstr(pwd);
	}
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

void	process(t_minishell *data, t_env **list)
{
	char	*line;
	int		i;

	i = 0;
	print_prompt(*list);
	if ((i = get_next_line(0, &line)) <= 0)
	{
		if (i == -1 && line == NULL)
			print_error_and_exit(_ENOMEM);
	}
	if (!(data->arg = ft_strsplitset(line, " \t")))
		print_error_and_exit(_ENOMEM);
	free(line);
	if (!data->arg[0])
		return ;
	if ((i = check_builtin(data)) >= 0)
	{
		if (get_expansions(data->arg, *list) == 0)
			return ;
		exec_builtin(data, i, list);
	}
	else
	{
		if ((data->valide_path = check_access(data)) == NULL)
		{
			print_error_first(_ENOCMD);
			ft_putendl_fd(data->arg[0], 2);
			return ;
		}
		if (access(data->valide_path, X_OK))
		{
			print_error_first(_ENOX);
			ft_putendl_fd(data->arg[0], 2);
			ft_strdel(&data->valide_path);
			return ;
		}
		if (get_expansions(data->arg, *list) == 0)
			return ;
		get_fork(data);
		ft_strdel(&data->valide_path);
	}
}
