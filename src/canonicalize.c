/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 02:40:03 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/23 08:38:03 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "minishell.h"

static char			*free_rpath(char *rpath)
{
	free(rpath);
	return (NULL);
}

static inline char	*substitute_link(t_realpath *vars, const char **name)
{
	char	buf[PATH_MAX];
	size_t	len;
	int		n;

	if (++vars->num_links > MAXSYMLINKS)
	{
		ft_set_errno(_ELOOP);
		return (NULL);
	}
	if ((n = readlink(vars->rpath, buf, PATH_MAX - 1)) < 0)
		return (NULL);
	buf[n] = '\0';
	len = ft_strlen(vars->end);
	if ((size_t)(n + len) >= PATH_MAX)
	{
		ft_set_errno(_ENAMETOOLONG);
		return (NULL);
	}
	ft_memmove(&vars->extra_buf[n], vars->end, len + 1);
	vars->end = ft_memcpy(vars->extra_buf, buf, n);
	*name = vars->end;
	if (buf[0] == '/')
		vars->dest = vars->rpath + 1;
	else if (vars->dest > vars->rpath + 1)
		while ((--vars->dest)[-1] != '/')
			;
	return ((void*)1);
}

static inline char	*substitute_path_component(const char **name,
		t_realpath *vars)
{
	struct stat	st;

	if (vars->dest[-1] != '/')
		*vars->dest++ = '/';
	if (vars->dest + (vars->end - vars->start) >= vars->rpath_limit
			&& realloc_rpath(vars) == NULL)
		return (NULL);
	ft_memcpy(vars->dest, vars->start, vars->end - vars->start);
	vars->dest += vars->end - vars->start;
	*vars->dest = '\0';
	if (stat(vars->rpath, &st) < 0)
		return (NULL);
	if (S_ISLNK(st.st_mode))
		return (substitute_link(vars, name));
	else if (!S_ISDIR(st.st_mode) && *vars->end != '\0')
	{
		ft_set_errno(_ENOTDIR);
		return (NULL);
	}
	return ((void*)1);
}

static inline char	*internal_realpath(const char *name, t_realpath *vars)
{
	vars->start = (char *)name;
	while (*vars->start)
	{
		while (*vars->start == '/')
			++vars->start;
		vars->end = vars->start;
		while (*vars->end && *vars->end != '/')
			++vars->end;
		if (vars->end - vars->start == 0)
			break ;
		else if (vars->end - vars->start == 2 && vars->start[0] == '.'
				&& vars->start[1] == '.' && vars->dest > vars->rpath + 1)
			while ((--vars->dest)[-1] != '/')
				;
		else if ((vars->end - vars->start > 1
					|| (vars->end - vars->start == 1 && vars->start[0] != '.'))
				&& substitute_path_component(&name, vars) == NULL)
			return (free_rpath(vars->rpath));
		vars->start = vars->end;
	}
	if (vars->dest > vars->rpath + 1 && vars->dest[-1] == '/')
		--vars->dest;
	*vars->dest = '\0';
	return (vars->rpath);
}

char				*ft_realpath(const char *name)
{
	t_realpath	vars;

	ft_memset(&vars, 0, sizeof(vars));
	if (!name)
	{
		ft_set_errno(_EINVAL);
		return (NULL);
	}
	if (name[0] == '\0')
	{
		ft_set_errno(_ENOENT);
		return (NULL);
	}
	if (!(vars.rpath = (char *)malloc(PATH_MAX)))
		return (NULL);
	vars.rpath_limit = vars.rpath + PATH_MAX;
	if (name[0] != '/')
	{
		if (getcwd(vars.rpath, PATH_MAX) == NULL)
			return (free_rpath(vars.rpath));
		vars.dest = vars.rpath + ft_strlen(vars.rpath);
	}
	else
	{
		vars.rpath[0] = '/';
		vars.dest = vars.rpath + 1;
	}
	return (internal_realpath(name, &vars));
}
