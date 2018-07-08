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
	return (path ? path + 5 : path);
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
	return (pwd ? pwd + 4 : pwd);
}

void	get_env(char **env, t_minishell *data)
{
	char *path;
	char *pwd;

	pwd = get_pwd(env);
	path = str_path(env);
	if (path)
		data->bin_dirs = ft_strsplit(path, ':');
	if (pwd)
		data->pwd = ft_strdup(pwd);
	get_dir(data);
}
