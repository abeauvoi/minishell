/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:14:16 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/25 07:32:31 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	if (!(join = (char*)malloc(len_s1 + ft_strlen(s2) + 1)))
		return (NULL);
	return (ft_strcpy(ft_strcpy(join, s1) + len_s1, s2));
}

char		*ft_strjoin2(char const *s1, char const *s2, size_t len_s1,
		size_t len_s2)
{
	char	*join;

	if (!(join = (char *)malloc(len_s1 + len_s2 + 1)))
		return (NULL);
	return (ft_strcpy(ft_strcpy(join, s1) + len_s1, s2));
}
