/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 19:29:22 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/05/23 07:35:38 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strchrset(const char *s, const char *charset)
{
	const char	*p;

	while (*charset)
	{
		if ((p = ft_strchr(s, *charset)) != NULL)
			return ((char *)p);
		++charset;
	}
	return (NULL);
}
