/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:57:58 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 05:53:42 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline size_t	ft_memmove_fast(t_u8 **dst, const t_u8 **src, size_t n)
{
	t_u64		*adst;
	const t_u64	*asrc;
	
	adst = (t_u64*)*dst;
	asrc = (t_u64*)*src;
	while (n >= BIG_BLOCK_SIZE)
	{
		*--adst = *--asrc;
		*--adst = *--asrc;
		*--adst = *--asrc;
		*--adst = *--asrc;
		n -= BIG_BLOCK_SIZE;
	}
	while (n >= LITTLE_BLOCK_SIZE)
	{
		*--adst = *--asrc;
		n -= LITTLE_BLOCK_SIZE;
	}
	*dst = (t_u8*)adst;
	*src = (const t_u8*)asrc;
	return (n);
}

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	t_u8		*d;
	const t_u8	*s;

	d = (t_u8 *)dst;
	s = (const t_u8 *)src;
	if (s < d && d < s + len)
	{
		s += len;
		d += len;
		if (!TOO_SMALL(len) && !UNALIGNED(s, d))
			len = ft_memmove_fast(&d, &s, len);
		while (len-- > 0)
			*--d = *--s;
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
