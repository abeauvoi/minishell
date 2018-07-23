/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 08:14:10 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/23 08:39:13 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"

char			*realloc_rpath(t_realpath *vars)
{
	size_t		new_size;
	ptrdiff_t	dest_offset;
	char		*new_rpath;

	dest_offset = vars->dest - vars->rpath;
	new_size = vars->rpath_limit - vars->rpath;
	new_size += (vars->end - vars->start + 1 > PATH_MAX ?
			vars->end - vars->start + 1 : PATH_MAX);
	if (!(new_rpath = (char *)malloc(new_size)))
	{
		ft_set_errno(_ENOMEM);
		return (NULL);
	}
	ft_memcpy(new_rpath, vars->rpath, vars->rpath_limit - vars->rpath + 1);
	free(vars->rpath);
	vars->rpath = new_rpath;
	vars->rpath_limit = vars->rpath + new_size;
	vars->dest = vars->rpath + dest_offset;
	return ((void*)1);
}
