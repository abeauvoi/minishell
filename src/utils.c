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
}
