/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 02:40:03 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/23 03:24:06 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_realpath(const char *name)
{
	char	*rpath;

	if (!name)
	{
		__set_errno(_EINVAL);
		return (NULL);
	}
	if (name[0] == '\0')
	{
		__set_errno(_ENOENT);
		return (NULL);
	}
	rpath = NULL;
	return (rpath);
}
