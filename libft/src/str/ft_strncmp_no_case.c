/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_no_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 17:45:41 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:33:25 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

static inline size_t	ft_strncmp_no_case_fast(const t_u8 **us1,
		const t_u8 **us2, size_t n)
{
	const t_u64		*as1;
	const t_u64		*as2;
	t_u64			mask;

	mask = 32;
	mask |= (mask << 8);
	mask |= (mask << 16);
	mask |= (mask << 32);
	as1 = (const t_u64 *)*us1;
	as2 = (const t_u64 *)*us2;
	while (n >= sizeof(long) && (mask | *as1) == (mask | *as2))
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

int						ft_strncmp_no_case(const char *s1, const char *s2,
		size_t n)
{
	const t_u8		*us1;
	const t_u8		*us2;

	if (!n)
		return (0);
	us1 = (const t_u8 *)s1;
	us2 = (const t_u8 *)s2;
	if (!UNALIGNED(s1, s2))
		n = ft_strncmp_no_case_fast(&us1, &us2, n);
	while (n-- > 0 && TO_LOWER(*us1) == TO_LOWER(*us2))
	{
		if (!n || !*us1)
			return (0);
		++us1;
		++us2;
	}
	return (*us1 - *us2);
}
