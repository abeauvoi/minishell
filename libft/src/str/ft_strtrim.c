/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:24:05 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:34:47 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strtrim(const char *s)
{
	char		*trim;
	const char	*end;
	size_t		len;

	end = s + ft_strlen(s) - 1;
	while (*s && ft_isblank(*s))
		++s;
	while (ft_isblank(*end))
		--end;
	len = end - s + 2;
	return (!(trim = (char *)malloc(len)) ? NULL :
			ft_strncpy(trim, s, len));
}
