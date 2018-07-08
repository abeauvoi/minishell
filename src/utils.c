#include "minishell.h"

char	*check_path(t_minishell *data)
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
