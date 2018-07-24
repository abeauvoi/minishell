/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:37:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/25 00:07:55 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

/*
** '-' is a special character, so in order to parse options, a '-' followed by
** '\0' is considered an argument.
*/

static int		parse_options(char **args, bool *no_symlinks)
{
	char	*p;
	int		i;

	i = 0;
	*no_symlinks = false;
	while (*args && (*args)[0] == '-' && (*args)[1] != '\0')
	{
		p = *args;
		while (*++p)
		{
			if (ft_strchr("LP", *p) == NULL)
			{
				ft_putstr("cd: -");
				ft_putchar(*p);
				ft_putendl(": invalid option:\n" BUILTIN_CD_USAGE);
				return (-1);
			}
			*no_symlinks = *p == 'P';
		}
		++args;
		++i;
	}
	return (i);
}

/*
** args should point to "cd"
*/

int			builtin_cd(t_env **env, char **args)
{
	bool	no_symlinks;
	bool	print_pwd;
	int		i;
	char	*curpath;
	char	cwd[PATH_MAX];

	if ((i = parse_options(++args, &no_symlinks)) != -1)
	{
		ft_bzero(cwd, PATH_MAX);
		args += i;
		print_pwd = false;
		if (*args && ft_strcmp(*args, "-") == 0)
		{
			print_pwd = true;
			curpath = ft_getenv(*env, "OLDPWD=", 7);
		}
		else if (!*args)
			curpath = ft_getenv(*env, "HOME=", 5);
		else
			curpath = (no_symlinks ? ft_realpath(*args) : *args);
		if (no_symlinks && !curpath && g_errno)
		{
			if (g_errno == _ENOMEM)
				print_error_and_exit(g_errno);
			print_error(g_errno);
			return (-1);
		}
		printf("[curpath:%s]\n", curpath);
		i = chdir(curpath);
		if (no_symlinks && *args && !print_pwd)
			free(curpath);
		if (i == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(curpath, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			builtin_setenv(env, "OLDPWD", ft_getenv(*env, "PWD=", 4));
			builtin_setenv(env, "PWD", getcwd(cwd, PATH_MAX - 1));
		}
		if (print_pwd)
			ft_putendl(ft_getenv(*env, "PWD=", 4));
		return (i);
	}
	return (0);
}
