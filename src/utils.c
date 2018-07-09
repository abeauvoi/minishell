#include "minishell.h"

t_env	*create_node(char *str)
{
	t_env	*new;

	if (!(new = malloc(sizeof(*new))) || !(new->str = ft_strdup(str)))
		return (NULL);
		new->next = NULL;
	return (new);
}

void	lst_push(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env		*set_list(t_minishell *data)
{
	t_env	*start;
	t_env	*new;
	int		i;

	start = NULL;
	i = 0;
	while (data->copy_env[i])
	{
		if (!(new = create_node(data->copy_env[i])))
			return (NULL);
		lst_push(&start, new);
		ft_putstr(data->copy_env[i]);
		i++;
	}
	return (start);
}

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
