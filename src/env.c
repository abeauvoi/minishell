#include "minishell.h"

void	init_builtin_tab(t_minishell *data)
{
	if (!(data->builtin = malloc(sizeof(char *) * 7)))
		print_error_and_exit(_ENOMEM);
	data->builtin[0] = "echo";
	data->builtin[1] = "cd";
	data->builtin[2] = "env";
	data->builtin[3] = "unsetenv";
	data->builtin[4] = "setenv";
	data->builtin[5] = "exit";
	data->builtin[6] = NULL;
}

char	*ft_getenv(t_env *list, const char *name, size_t len)
{
	char	*str;

	str = NULL;
	if (len < 1)
		return (str);
	while (list)
	{
		if (ft_strncmp(list->str, name, len) == 0)
		{
			str = list->str;
			break ;
		}
		list = list->next;
	}
	return (str ? str + len : str);
}

void	init_env(t_minishell *data, t_env *list)
{
	char *path;
	char *pwd;

	path = ft_getenv(list, "PATH=", sizeof("PATH=") - 1);
	if (path)
	{
		if (!(data->bin_dirs = ft_strsplit(path, ':')))
			print_error_and_exit(_ENOMEM);
	}
	pwd = ft_getenv(list, "PWD=", sizeof("PWD=") - 1);
	if (pwd)
	{
		if (!(data->pwd = ft_strdup(pwd)))
			print_error_and_exit(_ENOMEM);
	}
	list_to_tab(list, data);
}
