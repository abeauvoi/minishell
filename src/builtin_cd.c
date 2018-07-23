/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:37:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/23 08:47:20 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		parse_options(char **args, bool *no_symlinks)
{
	char	*p;
	int		pos_arg;

	pos_arg = 0;
	while (*args && (*args)[0] == '-')
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
		++pos_arg;
	}
	return (pos_arg);
}

/*
** args should point to "cd"
*/

int			builtin_cd(t_env **env, char **args)
{
	bool	no_symlinks;
	bool	print_pwd;
	int		pos_arg;
	char	*curpath;
	int		r;

	no_symlinks = false;
	if ((pos_arg = parse_options(&args[1], &no_symlinks)) != -1)
	{
		args += pos_arg + 1;
		print_pwd = false;
		if (*args && !ft_strcmp(*args, "-"))
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
		r = chdir(curpath);
		if (no_symlinks && *args && !print_pwd)
			free(curpath);
		if (r < 0)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(curpath, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			builtin_setenv(env, "OLDPWD", ft_getenv(*env, "PWD=", 4));
			builtin_setenv(env, "PWD", *args);
		}
		if (print_pwd)
			ft_putendl(ft_getenv(*env, "PWD=", 4));
		return (r);
	}
	return (0);
}
