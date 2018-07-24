/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:15:23 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 05:34:26 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

int				ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const t_u8	*us1;
	const t_u8	*us2;
	const t_u64	*as1;
	const t_u64	*as2;

	us1 = (const t_u8 *)s1;
	us2 = (const t_u8 *)s2;
	if (!UNALIGNED(us1, us2) && !TOO_SMALL(n))
	{
		as1 = (const t_u64*)us1;
		as2 = (const t_u64*)us2;
		while (n >= LITTLE_BLOCK_SIZE && *as1 == *as2)
		{
			++as1;
			++as2;
			n -= LITTLE_BLOCK_SIZE;
		}
		us1 = (const t_u8*)as1;
		us2 = (const t_u8*)as2;
	}
	while (n-- > 0 && *us1++ == *us2++)
		continue ;
	if (n)
		return (*us1 - *us2);
	return (0);
}
