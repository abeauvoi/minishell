#include "minishell.h"

#include <stdio.h>
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
	if (access(data->arg[0], F_OK) == 0)
	{
		if (!(tmp2 = ft_strdup(data->arg[0])))
			print_error_and_exit(_ENOMEM);
		return (tmp2);
	}
	if (data->bin_dirs)
	{
		while (data->bin_dirs[i])
		{
			if (!(tmp = ft_strjoin(data->bin_dirs[i], "/")))
				print_error_and_exit(_ENOMEM);
			if (!(tmp2 = ft_strjoin(tmp, data->arg[0])))
				print_error_and_exit(_ENOMEM);
			ft_strdel(&tmp);
			if (access(tmp2, F_OK) == 0)
				return (tmp2);
			ft_strdel(&tmp2);
			i++;
		}
	}
	return (NULL);
}
