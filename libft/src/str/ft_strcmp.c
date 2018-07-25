/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:41:24 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 06:37:49 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_macros.h"
#include "libft_types.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	const t_u8	*us1;
	const t_u8	*us2;
	const t_u64	*as1;
	const t_u64	*as2;

	us1 = (const t_u8 *)s1;
	us2 = (const t_u8 *)s2;
	if (!UNALIGNED(us1, us2))
	{
		as1 = (const t_u64*)us1;
		as2 = (const t_u64*)us2;
		while (!DETECT_NULL(*as1) && *as1++ == *as2++)
			continue ;
		us1 = (const t_u8*)as1;
		us2 = (const t_u8*)as2;
	}
	while (*us1 && *us1++ == *us2++)
		continue ;
	return (*us1 - *us2);
}
