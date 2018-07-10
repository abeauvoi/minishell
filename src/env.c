#include "minishell.h"

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

char	*str_path(t_env *list)
{
	char *path;

	path = NULL;
	while (list)
	{
		if (ft_strncmp(list->str, "PATH=", 5) == 0)
		{
			path = list->str;
			break ;
		}
		list = list->next;
	}
	return (path ? path + 5 : path);
}

char	*get_pwd(t_env *list)
{
	char *pwd;

	pwd = NULL;
	while (list)
	{
		if (ft_strncmp(list->str, "PWD=", 4) == 0)
		{
			pwd = list->str;
			break ;
		}
		list = list->next;
	}
	return (pwd ? pwd + 4 : pwd);
}

void	get_env(t_minishell *data, t_env *list)
{
	char *path;
	char *pwd;

	pwd = get_pwd(list);
	path = str_path(list);
	if (path)
		data->bin_dirs = ft_strsplit(path, ':');
	if (pwd)
		data->pwd = ft_strdup(pwd);
	get_dir(data);
	list_to_tab(list, &data);
}
