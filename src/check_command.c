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

int		check_builtin(t_minishell *data)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(data->arg[0], data->builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*check_access(t_minishell *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (data->bin_dirs[i])
	{
		tmp = ft_strjoin(data->bin_dirs[i], "/");
		tmp2 = ft_strjoin(tmp, data->arg[0]);
		ft_strdel(&tmp);
		if (access(tmp2, F_OK) == 0)
			return (tmp2);
		ft_strdel(&tmp2);
		i++;
	}
	return (NULL);
}
