/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 20:44:28 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:30:03 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_types.h"
#include "libft_macros.h"

static void				ft_memccpy_long_word(t_u8 **d, const t_u8 **s, t_u8 c,
		size_t n)
{
	t_u64		*ld;
	t_u64		*ls;
	t_u64		mask;

	ld = (t_u64*)*d;
	ls = (t_u64*)*s;
	mask = c;
	mask |= (mask << 8);
	mask |= (mask << 16);
	mask |= (mask << 32);
	while (n >= LITTLE_BLOCK_SIZE && !DETECT_CHAR(*ls, mask))
	{
		*ls++ = *ld++;
		n -= LITTLE_BLOCK_SIZE;
	}
	*s = (t_u8*)ls;
	*d = (t_u8*)ld;
}

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	t_u8		*d;
	const t_u8	*s;
	t_u8		uc;

	s = (const t_u8 *)src;
	d = (t_u8 *)dst;
	uc = (t_u8)c;
	while (n-- > 0 && UNALIGNED(s, d))
		if ((*d++ = *s++) == uc)
			return (d);
	if (!TOO_SMALL(n))
	{
		ft_memccpy_long_word(&d, &s, uc, n);
		n &= LITTLE_BLOCK_SIZE - 1;
	}
	while (n-- > 0)
		if ((*d++ = *s++) == uc)
			return (d);
	return (NULL);
}
