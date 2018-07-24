/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 23:53:21 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:36:03 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

int			ft_strchr2(const char *const str, char c)
{
	const char	*s;
	t_u64		mask;
	const t_u64	*lptr;

	s = str;
	if (!_UNALIGNED(s))
	{
		mask = c;
		mask |= mask << 8;
		mask |= mask << 16;
		mask |= mask << 32;
		lptr = (t_u64*)s;
		while (!DETECT_NULL(*lptr) && !DETECT_CHAR(*lptr, mask))
			++lptr;
		s = (const char *)lptr;
	}
	while (*s && *s != c)
		++s;
	if (*s == c)
		return (s - str);
	return (-1);
}
