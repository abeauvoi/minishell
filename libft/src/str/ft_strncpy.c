/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:52:48 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:19:54 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

char		*ft_strncpy(char *dst0, const char *src0, size_t len)
{
	char		*dst;
	const long	*asrc;
	long		*adst;

	dst = dst0;
	if (!TOO_SMALL(len) && !UNALIGNED(src0, dst))
	{
		asrc = (const long *)src0;
		adst = (long *)dst0;
		while (len >= LITTLE_BLOCK_SIZE && !DETECT_NULL(*asrc))
		{
			len -= LITTLE_BLOCK_SIZE;
			*adst++ = *asrc++;
		}
		src0 = (const char *)asrc;
		dst = (char *)adst;
	}
	while (len-- > 0)
	{
		*dst++ = *src0;
		if (*src0)
			++src0;
	}
	return (dst0);
}
