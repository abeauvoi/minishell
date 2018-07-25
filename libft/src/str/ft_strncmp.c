/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:43:42 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:32:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

static inline size_t	ft_strncmp_fast(const t_u8 **us1,
		const t_u8 **us2, size_t n)
{
	const t_u64		*as1;
	const t_u64		*as2;

	as1 = (const t_u64 *)*us1;
	as2 = (const t_u64 *)*us2;
	while (n >= sizeof(long) && *as1 == *as2)
	{
		n -= sizeof(long);
		if (!n || DETECT_NULL(*as1))
			return (0);
		++as1;
		++as2;
	}
	*us1 = (const t_u8 *)as1;
	*us2 = (const t_u8 *)as2;
	return (n);
}

int						ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const t_u8		*us1;
	const t_u8		*us2;

	if (!n)
		return (0);
	us1 = (const t_u8 *)s1;
	us2 = (const t_u8 *)s2;
	if (!UNALIGNED(s1, s2))
		n = ft_strncmp_fast(&us1, &us2, n);
	while (n-- > 0 && *us1 == *us2)
	{
		if (!n || !*us1)
			return (0);
		++us1;
		++us2;
	}
	return (*us1 - *us2);
}
