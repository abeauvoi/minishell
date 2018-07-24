/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 19:03:26 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 06:22:19 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

char	*ft_strchr(const char *s, int c)
{
	t_u8		uc;
	t_u64		mask;
	const t_u64	*lptr;

	uc = (t_u8)c;
	if (!_UNALIGNED(s))
	{
		mask = uc;
		mask |= mask << 8;
		mask |= mask << 16;
		mask |= mask << 32;
		lptr = (t_u64*)s;
		while (!DETECT_NULL(*lptr) && !DETECT_CHAR(*lptr, mask))
			++lptr;
		s = (const char *)lptr;
	}
	while (*s && *s != uc)
		++s;
	if (*s == uc)
		return ((char *)s);
	return (NULL);
}
