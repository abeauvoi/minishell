/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 01:23:26 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/22 03:46:24 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*remplace_tilde(char *arg, t_env *env, size_t arglen)
{
	char	*data;
	char	*result;

	if ((data = _getenv(env, "HOME=", 5)) != NULL)
	{
		if (arglen == 1)
			result = ft_strdup(data);
		else if (data[ft_strlen(data) - 1] == '/')
			result = ft_strjoin(data, arg + 2);
		else
			result = ft_strjoin(data, arg + 1);
		free(arg);
		return (result);
	}
	return (NULL);
}

static char		*get_user(char *user)
{
	char *tmp;

	tmp = ft_strjoin("/Users/", user + 1);
	ft_strdel(&user);
	return (tmp);
}

static int	get_tilde(char **arg, t_env *env)
{
	void	*tmp;

	if ((!ft_strncmp(*arg, "setenv", 6)) || (!ft_strncmp(*arg, "unsetenv", 8)))
		return (1);
	if ((*arg)[1] == '/' || !(*arg)[1])
	{
		if ((*arg = remplace_tilde(*arg, env, ft_strlen(*arg))))
			return (1);
		ft_putendl("please, set the variable HOME to use ~");
		return (0);
	}
	else
	{
		if ((tmp = getpwnam((*arg) + 1)) == NULL)
		{
			ft_putstr("Unknown user: ");
			ft_putendl((*arg) + 1);
		}
		else
			*arg = get_user(*arg);
		return (!!tmp);
	}
	return (1);
}

static int		replace_dollars(char **arg, char *p, t_env *env)
{
	char	*tmp;
	char	*tmp2;
	char	*data;
	char	*tmp3;

	tmp = p + 1;
	while (*tmp && *tmp != '$' && *tmp != '/')
		++tmp;
	if ((data = _getenv(env, p + 1, (tmp - p) - 1)) != NULL)
	{
		tmp2 = ft_strsub(*arg, 0, (p - *arg));
		tmp3 = ft_strjoin(tmp2, data + 1);
		ft_strdel(&tmp2);
		tmp2 = ft_strdup(tmp);
		free(*arg);
		*arg = ft_strjoin(tmp3, tmp2);
		ft_strdel(&tmp3);
		ft_strdel(&tmp2);
		return (1);
	}
	ft_putstr(p + 1);
	ft_putendl(": Undefinedvariable.");
	return (0);
}

int		get_dollars(char **arg, t_env *env)
{
	char	*p;

	p = *arg;
	while (*p)
	{
		if (*p == '$')
		{
			if (*(p + 1) == '$')
			{
				while (*p && *p == '$')
					p++;
			}
			if (*(p + 1) != '\0')
			{
				if (replace_dollars(arg, p, env) == 0)
					return (0);
				else
					return (get_dollars(arg, env));
			}
			return (1);
		}
		else
			p++;
	}
	return (1);
}

int		get_expansions(char **args, t_env *env)
{
	while (*(++args) != NULL)
	{
		if (*args[0] == '~' && get_tilde(args, env) == 0)
			return (0);
		if (get_dollars(args, env) == 0)
			return (0);
	}
	return (1);
}
