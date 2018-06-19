#include "minishell.h"

char	*str_path(char **env)
{
	char *path;

	path = NULL;
	while (*env != 0)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env;
			break ;
		}
		env++;
	}
	return (path);
}

void	tab_path(char **env, t_minishell *data)
{
	char *tmp;

	tmp = ft_strnew(1);
	data->path = ft_strsplit(str_path(env), '=');
	ft_strcpy(tmp, data->path[1]);
	data->path = ft_strsplit(tmp, ':');
	ft_strdel(&tmp);
}

char	*get_pwd(char **env)
{
	char *pwd;

	pwd = NULL;
	while (*env != 0)
	{
		if (ft_strncmp(*env, "PWD=", 4) == 0)
		{
			pwd = *env;
			break ;
		}
		env++;
	}
	return (pwd);
}

void	get_env(char **env, t_minishell *data)
{
	char **tmp;

	tab_path(env, data);
	tmp = ft_strsplit(get_pwd(env), '=');
	data->pwd = ft_strdup(tmp[1]);
}
