/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:51:49 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/08/06 01:47:22 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"
#include "libft_macros.h"

char	*ft_strchrnul(const char *s, int c)
{
	t_u8 		uc;
	t_u64 		mask;
	const t_u64 *lptr;

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
	return ((char *)s);
}
