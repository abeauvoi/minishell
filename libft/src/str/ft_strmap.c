/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 22:35:35 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 06:57:36 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char				*ft_strmap(char const *s, char (*f)(char))
{
	char			*new;
	unsigned int	i;

	if (!(new = (char *)malloc(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (*s)
		new[i++] = f(*s++);
	return (new);
}

char				*ft_strmap2(char const *s, char (*f)(char), size_t n)
{
	char			*new;
	char			*tmp;

	if (!(new = (char *)malloc(n + 1)))
		return (NULL);
	tmp = new;
	while (*s)
		*tmp++ = f(*s++);
	return (new);
}
