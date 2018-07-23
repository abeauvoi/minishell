/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 02:40:03 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/23 06:09:26 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*free_rpath(char *rpath)
{
	free(rpath);
	return (NULL);
}

static inline char	*handle_link(int *num_links, char **extra_buf,
		char **name, char **end)
{
	char buf[PATH_MAX];
	size_t len;

	if (++*num_links > MAXSYMLINKS)
	{
		__set_errno(_ELOOP);
		return (NULL);
	}
	if ((n = readlink(rpath, buf, PATH_MAX - 1)) < 0)
		return (NULL);
	buf[n] = '\0';
	if (!*extra_buf && !(*extra_buf = (char *)malloc(PATH_MAX)))
	{
		__set_errno(_ENOMEM);
		return (NULL);
	}
	len = ft_strlen(*end);
	if ((size_t)(n + len) >= PATH_MAX)
	{
		__set_errno(_ENAMETOOLONG);
		return (NULL);
	}
	ft_memmove(&(*extra_buf)[n], end, len + 1);
	*end = memcpy(*extra_buf, buf, n);
	*name = *end;
	if (buf[0] == '/')
		dest = rpath + 1;
	else if (dest > rpath + 1)
		while ((--dest)[-1] != '/')
			;
	return (rpath);
}
static inline char	*substitute_path_component(const char *name, char *rpath,
		char *dest, char **rpath_limit)
{
	struct stat	st;
	size_t		new_size;
	ptrdiff_t	dest_offset;
	char		*new_rpath;

	if (dest[-1] != '/')
		*dest++ = '/';
	if (dest + (end - start) >= *rpath_limit)
	{
		dest_offset = dest - rpath;
		new_size = *rpath_limit - rpath;
		new_size += (end - start + 1 > PATH_MAX ? end - start + 1 : PATH_MAX);
		if (!(new_rpath = (char *)malloc(new_size)))
			return (NULL);
		ft_memcpy(new_rpath, rpath, *rpath_limit - rpath + 1);
		free(rpath);
		rpath = new_rpath;
		*rpath_limit = rpath + new_size;
		dest = rpath + dest_offset;
	}
	ft_memcpy(dest, start, end - start);
	dest += end - start;
	*dest = '\0';
	if (stat(rpath, &st) < 0)
		return (NULL);
	if (S_ISLNK(st.st_mode))
	{
	}
	else if (!S_ISDIR(st.st_mode) && *end != '\0')
	{
		__set_errno(_ENOTDIR);
		return (NULL);
	}
	return (rpath);
}

static inline char	*internal_realpath(const char *name, char *rpath,
		char *dest, char *rpath_limit)
{
	char		*start;
	char		*end;
	char		*extra_buf;
	int			n;
	int			num_links;

	num_links = 0;
	start = name;
	while (*start)
	{
		while (*start == '/')
			++start;
		end = start;
		while (*end && *end != '/')
			++end;
		if (end - start == 0)
			break ;
		else if (end - start == 1 && start[0] == '.')
			;
		else if (end - start == 2 && start[0] == '.' && start[1] == '.'
				&& dest > rpath + 1)
			while ((--dest)[-1] != '/')
				;
		else
		{
		}
		start = end;
	}
	if (dest > rpath + 1 && dest[-1] == '/')
		--dest;
	*dest = '\0';
	return (rpath);
}

char				*_realpath(const char *name)
{
	char	*rpath;
	char	*rpath_limit;
	char	*dest;

	if (!name)
	{
		__set_errno(__EINVAL);
		return (NULL);
	}
	if (name[0] == '\0')
	{
		__set_errno(__ENOENT);
		return (NULL);
	}
	if (!(rpath = (char *)malloc(PATH_MAX)))
		return (NULL);
	rpath_limit = rpath + PATH_MAX;
	if (name[0] != '/')
	{
		if (!getcwd(rpath, PATH_MAX))
			return (free_rpath(rpath));
		dest = ft_memchr(rpath, '\0');
	}
	else
	{
		rpath[0] = '/';
		dest = rpath + 1;
	}
	return (internal_realpath(name, rpath, dest, rpath_limit));
}
