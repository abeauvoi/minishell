/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 05:13:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/18 07:19:58 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_echo(char **args, size_t total_length)
{
	char	*output;
	char	*tmp;

	if (!(output = ft_strnew(total_length)))
		;
	tmp = output;
	while (*args)
	{
		ft_strcpy(tmp, *args);
		tmp += ft_strlen(*args);
		++args;
		if (args)
			*tmp++ = ' ';
	}
	ft_putendl(output);
	ft_strdel(&output);
}

void		builtin_env(t_env *env)
{
	while (env)
	{
		ft_putendl(env->str);
		env = env->next;
	}
}

int			check_name(char *name)
{
	int		i;

	i = 1;
	if ((name[0] < 'A' || name[0] > 'Z') && (name[0] < 'a' || name[0] > 'z'))
		return (0);
	while (name[i])
	{
		if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z')
				&& (name[i] < '0' || name[i] > '9') && !(name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void		builtin_setenv(t_env **env, char *name, char *content)
{
	char	*tmp2;
	int		len;
	char	*tmp;
	t_env	*new;
	t_env	*ptr;

	if (check_name(name) == 1)
	{
		ft_putendl("setenv: Variable name must contain alphanumeric characters "
				"and must begin with a letter.");
		return ;
	}
	len = ft_strlen(name);
	if (content)
	{
		tmp2 = ft_strjoin(name, "=");
		tmp = ft_strjoin(tmp2, content);
		ft_strdel(&tmp2);
	}
	else
		tmp = ft_strjoin(name, "=");
	ptr = *env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->str, name, len))
		{
			free(ptr->str);
			ptr->str = ft_strdup(tmp);
			free(tmp);
			return ;
		}
		ptr = ptr->next;
	}
	new = create_node(tmp);
	lst_push(env, new);
	ft_strdel(&tmp);
}

void		builtin_unsetenv(t_env **env, char *arg, size_t len)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = tmp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, arg, len))
		{
			lst_del(env, tmp, prev);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
