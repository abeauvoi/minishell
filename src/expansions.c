/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 01:23:26 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/18 06:56:05 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tilde(char *arg, char **env)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", 5))
		{
			tmp = ft_strdup(arg + 1);
			tmp2 = ft_strdup(env[i] + 5);
			ft_strdel(&arg);
			arg = ft_strjoin(tmp2, tmp);
			ft_strdel(&tmp);
			ft_strdel(&tmp2);
			return (arg);
		}
		i++;
	}
	return (NULL);
}

char		*get_user(char *user)
{
	char *tmp;

	tmp = ft_strdup(user + 1);
	ft_strdel(&user);
	user = ft_strjoin("/Users/", tmp);
	ft_strdel(&tmp);
	return (user);
}

int		get_expansions(char **arg, char **env)
{
	int		i;

	i = 1;
	if ((!ft_strncmp(arg[0], "setenv", 6)) || (!ft_strncmp(arg[0], "unsetenv", 8)))
		return (1);
	while (arg[i])
	{
		if (arg[i][0] == '~')
		{
			if (arg[i][1] == '/' || ft_strlen(arg[i]) == 1)
			{
				if ((arg[i] = get_tilde(arg[i], env)) == NULL)
				{
					ft_putendl("please, set the variable HOME to use ~");
					return (0);
				}
			}
			else
			{
				if (getpwnam(arg[i] + 1) == NULL)
				{
					ft_putstr("Unknown user: ");
					ft_putendl(arg[i] + 1);
					return (0);
				}
				else
				{
					arg[i] = get_user(arg[i]);
					return (1);
				}
			}
		}
		//if (arg[i][0] == '$')
		//	get_dollars(arg[i], env);
		i++;
	}
	return (1);
}
