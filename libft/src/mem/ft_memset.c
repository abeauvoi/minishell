/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:43:39 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/25 05:03:43 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

static inline t_u8	*ft_memset_fast(t_u8 *dst, unsigned long buffer,
		size_t n)
{
	while (n >= LITTLE_BLOCK_SIZE * 4)
	{
		*((t_u64*)dst) = buffer;
		dst += LITTLE_BLOCK_SIZE;
		*((t_u64*)dst) = buffer;
		dst += LITTLE_BLOCK_SIZE;
		*((t_u64*)dst) = buffer;
		dst += LITTLE_BLOCK_SIZE;
		*((t_u64*)dst) = buffer;
		dst += LITTLE_BLOCK_SIZE;
		n -= LITTLE_BLOCK_SIZE * 4;
	}
	while (n >= LITTLE_BLOCK_SIZE)
	{
		*((t_u64*)dst) = buffer;
		dst += LITTLE_BLOCK_SIZE;
		n -= LITTLE_BLOCK_SIZE;
	}
	return (dst);
}

void				*ft_memset(void *dst0, int c, size_t n)
{
	t_u8	*dst;
	t_u8	uc;
	t_u64	buffer;

	if (!n)
		return (0);
	dst = (t_u8 *)dst0;
	uc = (t_u8)c;
	while (_UNALIGNED(dst))
	{
		*dst++ = uc;
		if (--n == 0)
			return (dst0);
	}
	if (!TOO_SMALL(n))
	{
		buffer = c;
		buffer |= (buffer << 8);
		buffer |= (buffer << 16);
		buffer |= (buffer << 32);
		dst = ft_memset_fast(dst, buffer, n);
		n &= (LITTLE_BLOCK_SIZE - 1);
	}
	while (n-- > 0)
		*dst++ = uc;
	return (dst0);
}
