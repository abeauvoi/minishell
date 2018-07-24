/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:34:45 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 05:54:25 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline size_t	ft_memcpy_fast(t_u8 **dst, const t_u8 **src,
		size_t len)
{
	t_u64		*adst;
	const t_u64	*asrc;

	adst = (t_u64 *)*dst;
	asrc = (const t_u64 *)*src;
	while (len >= BIG_BLOCK_SIZE)
	{
		*adst++ = *asrc++;
		*adst++ = *asrc++;
		*adst++ = *asrc++;
		*adst++ = *asrc++;
		len -= BIG_BLOCK_SIZE;
	}
	while (len >= LITTLE_BLOCK_SIZE)
	{
		*adst++ = *asrc++;
		len -= LITTLE_BLOCK_SIZE;
	}
	*dst = (t_u8 *)adst;
	*src = (const t_u8 *)asrc;
	return (len);
}

void					*ft_memcpy(void *dst0, const void *src0, size_t len)
{
	t_u8		*dst;
	const t_u8	*src;

	src = (const t_u8 *)src0;
	dst = (t_u8 *)dst0;
	if (!TOO_SMALL(len) && !UNALIGNED(src, dst))
		len = ft_memcpy_fast(&dst, &src, len);
	while (len-- > 0)
		*dst++ = *src++;
	return (dst);
}
