/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 22:23:13 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:31:02 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

void	ft_strclr(char *s)
{
	t_u64	*lptr;

	while (_UNALIGNED(s))
	{
		if (!*s)
			return ;
		*s++ = 0;
	}
	lptr = (t_u64*)s;
	while (!DETECT_NULL(*lptr))
		*lptr++ = 0;
	s = (char *)lptr;
	while ((*s++ = 0))
		continue ;
}
