/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:37:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/20 01:39:55 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_options(char **args, bool *follow_symlinks)
{
	char	*p;
	int		pos_arg;

	pos_arg = 0;
	while (*args && (*args)[0] == '-')
	{
		p = *args;
		while (*++p)
		{
			if (ft_strchr("LP", *p) != NULL)
				*follow_symlinks = *p == 'L';
			else
			{
				ft_putstr("cd: -");
				ft_putchar(*p);
				ft_putendl(": invalid option:\n" BUILTIN_CD_USAGE);
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
	bool	print_pwd;
	int		pos_arg;
	char	*curpath;

	follow_symlinks = true;
	if ((pos_arg = parse_options(args, &follow_symlinks)) != -1)
	{
		args += pos_arg;
		print_pwd = false;
		if (args[0] && !ft_strcmp(args[0], "-"))
		{
			print_pwd = true;
			curpath = _getenv(*env, "OLDPWD=", 7);
		}
		else if (!args[0])
			curpath = _getenv(*env, "HOME=", 5);
		else
			curpath = args[0];
		builtin_setenv(env, "OLDPWD=", _getenv(*env, "PWD=", 4));
		builtin_setenv(env, "PWD=", args[0]);
		if (print_pwd)
			ft_putendl(_getenv(*env, "PWD=", 4));
		return (chdir(curpath));
	}
	return (0);
}
