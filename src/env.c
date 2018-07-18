#include "minishell.h"

void	init_builtin_tab(t_minishell *data)
{
	if (!(data->builtin = malloc(sizeof(char *) * 7)))
		return ;
	data->builtin[0] = "echo";
	data->builtin[1] = "cd";
	data->builtin[2] = "env";
	data->builtin[3] = "unsetenv";
	data->builtin[4] = "setenv";
	data->builtin[5] = "exit";
}

void	get_dir(t_minishell *data)
{
	char	**tmp;
	int		i;

	tmp = ft_strsplit(data->pwd, '/');
	i = 0;
	while (tmp[i])
		i++;
	data->dir = ft_strdup(tmp[i - 1]);
	i = 0;
	while (tmp[i])
		ft_strdel(tmp + i++);
	free(tmp);
}

char	*_getenv(t_env *list, const char *name, size_t len)
{
	char	*str;

	str = NULL;
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

	pwd = _getenv(list, "PWD=", sizeof("PWD=") - 1);
	path = _getenv(list, "PATH=", sizeof("PATH=") - 1);
	if (path)
		data->bin_dirs = ft_strsplit(path, ':');
	if (pwd)
		data->pwd = ft_strdup(pwd);
	get_dir(data);
	list_to_tab(list, data);
}
