/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:14:16 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/30 20:41:39 by abeauvoi         ###   ########.fr       */
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
	ft_strcpy(join, s1);
	ft_strcpy(join + len_s1, s2);
	return (join);
}

char		*ft_strjoin2(char const *s1, char const *s2, size_t len_s1,
		size_t len_s2)
{
	char	*join;

	if (!(join = (char *)malloc(len_s1 + len_s2 + 1)))
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + len_s1, s2);
	return (join);
}
