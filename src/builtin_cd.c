/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:37:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/18 05:57:09 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_options(char **args, bool *follow_symlinks)
{
	char	*p;
	int		pos_arg;

	pos_arg = 0;
	while (*args && *args[0] == '-')
	{
		p = *args;
		while (*++p)
		{
			if (ft_strchr("LP", *p) != NULL)
				*follow_symlinks = *p == 'L';
			else
			{
				ft_putendl("Invalid option:\n" BUILTIN_CD_USAGE);
				return (-1);
			}

		}
		++args;
		++pos_arg;
	}
	return (pos_arg);
}

/*
** args should point to "cd"
*/

int			builtin_cd(t_env **env, char **args)
{
	bool	follow_symlinks;
	int		pos_arg;

	follow_symlinks = true;
	if ((pos_arg = parse_options(&args[1], &follow_symlinks)) != -1)
	{
		print_pwd = false;
		args += pos_arg;
		if (!*args)
			return (chdir(getenv(*env, "HOME=", sizeof("HOME=") - 1)));
		if (args[0][0] == '-' && args[0][1] == '\0')
		{
		}
	}
	return (0);
}
