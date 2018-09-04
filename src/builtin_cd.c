/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 00:37:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/09/04 20:41:47 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include "minishell.h"
#include "ft_printf.h"

/*
** '-' is a special character, so in order to parse options, a '-' followed by
** '\0' is considered as an argument.
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
			if (ft_strchr("LP", *p) != NULL)
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

static char	*join_pwd_to_arg(char *operand)
{
	char	buf[PATH_MAX];
	char	*ptr;
	char	*curpath;
	size_t	strlen_operand;

	if (!(ptr = getcwd(buf, PATH_MAX)))
		return (ft_set_errno2(_EGETCWD));
	ptr += ft_strlen(buf);
	*ptr++ = '/';
	strlen_operand = ft_strlen(operand);
	if (ptr + strlen_operand > buf + PATH_MAX)
		return (ft_set_errno2(_ENAMETOOLONG));
	ft_strcpy(ptr, operand);
	if (!(curpath = ft_strdup(buf)))
		return (ft_set_errno2(_ENOMEM));
	return (curpath);
}

/*
** POSIX-compliant implementation.
** See https://www.unix.com/man-page/posix/1posix/cd/ for more details.
*/

static char	*parse_cdpath(char *arg, bool *print_pwd, char *cdpath)
{
	char			buf[PATH_MAX];
	char 			*ptr;
	char 			*next_component;
	size_t 			len_pathname;
	struct stat 	stats;
	
	while (*cdpath)
	{
		next_component = ft_strchrnul(cdpath, ':');
		len_pathname = next_component - cdpath;
		if (len_pathname > 0)
			ptr = ft_strncpy(buf, cdpath, len_pathname) + len_pathname;
		else
		{
			ptr = buf;
			*ptr++ = '.';
		}
		*ptr++ = '/';
		if (ptr + ft_strlen(arg) > buf + PATH_MAX)
			return (ft_set_errno2(_ENAMETOOLONG));
		ft_strcpy(ptr, arg);
		if (access(buf, X_OK) == 0 && stat(buf, &stats) == 0
				&& S_ISDIR(stats.st_mode))
		{
			*print_pwd = true;
			return (ft_strdup(buf));
		}
		cdpath = next_component + !!*next_component;
	}
	return (NULL);
}

static char	*set_curpath(t_env *env, char *arg, bool *print_pwd,
		bool *curpath_is_mallocd)
{
	char	*cdpath;
	char 	*new_path;

	*curpath_is_mallocd = false;
	if (!arg)
		return ((new_path = ft_getenv(env, "HOME=", 5)) ? new_path :
				ft_set_errno2(_ENOHOME));
	else if (arg[0] == '/')
		return (arg);
	else if (arg[0] == '-' && arg[1] == '\0')
	{
		*print_pwd = true;
		return ((new_path = ft_getenv(env, "OLDPWD=", 7)) ? new_path :
			ft_set_errno2(_ENOOLDPWD));
	}
	else if ((cdpath = ft_getenv(env, "CDPATH=", 7)) &&
			(new_path = parse_cdpath(arg, print_pwd, cdpath)))
	{
		*curpath_is_mallocd = true;
		return (new_path);
	}
	else
	{
		*curpath_is_mallocd = true;
		return (join_pwd_to_arg(arg));
	}
}

int			builtin_cd(t_env **env, char **argv)
{
	bool	no_symlinks;
	bool 	curpath_is_mallocd;
	bool	print_pwd;
	int		ret;
	char	*curpath;
	char	cwd[PATH_MAX];

	if ((ret = parse_options(++argv, &no_symlinks)) != -1)
	{
		ft_bzero(cwd, PATH_MAX);
		argv += ret;
		print_pwd = false;
		curpath = set_curpath(*env, *argv, &print_pwd, &curpath_is_mallocd);
		if (!curpath)
			return (-1);
		ret = chdir(curpath); 
		if (curpath_is_mallocd)
			free(curpath);
		if (ret == -1)
			return (ft_set_errno(_ENOENT));
		else
		{
			builtin_setenv(env, "OLDPWD", ft_getenv(*env, "PWD=", 4));
			builtin_setenv(env, "PWD", getcwd(cwd, PATH_MAX - 1));
		}
		if (print_pwd)
			ft_putendl(ft_getenv(*env, "PWD=", 4));
	}
	return (ret);
}
