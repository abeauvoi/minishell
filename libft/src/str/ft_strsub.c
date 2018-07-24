/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:06:00 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:24:41 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*sub;

	++len;
	if (!(sub = (char *)malloc(len)))
		return (NULL);
	return (ft_strncpy(sub, s + start, len));
}
