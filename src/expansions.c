/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 01:23:26 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/13 01:48:38 by jolabour         ###   ########.fr       */
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

int		get_expansions(char **arg, char **env)
{
	int		i;

	i = 1;
	if (!ft_strncmp(arg[0], "setenv", 6))
		i = 2;
	else if (!ft_strncmp(arg[0], "unsetenv", 8))
		return (1);
	while (arg[i])
	{
		if ((arg[i][0] == '~' && ((arg[i] = get_tilde(arg[i], env)) == NULL && arg[i])) || (ft_strlen(arg[i]) > 1 && arg[i][1] != '/'))
				return (0);
		//if (arg[i][0] == '$')
		//	get_dollars(arg[i], env);
		i++;
	}
	return (1);
}
