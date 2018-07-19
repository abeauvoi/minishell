/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 01:23:26 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/19 04:03:38 by jolabour         ###   ########.fr       */
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

int		get_expansions(char **arg, t_env *env)
{
	if ((!ft_strncmp(*arg, "setenv", 6)) || (!ft_strncmp(*arg, "unsetenv", 8)))
		return (1);
	while (*++arg)
	{
		if (*arg[0] == '~' && get_tilde(arg, env) == 0)
			return (0);
		//if (get_dollars(*arg, env) == 0)
		//	return (0);
	}
	return (1);
}
