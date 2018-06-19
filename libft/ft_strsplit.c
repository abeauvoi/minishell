/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 02:32:26 by jolabour          #+#    #+#             */
/*   Updated: 2017/11/20 07:40:07 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_world(char const *s, char c)
{
	int		i;
	int		word;
	int		is_word;

	i = 0;
	is_word = 0;
	word = 0;
	while (s[i])
	{
		if (is_word == 1 && s[i] == c)
			is_word = 0;
		if (is_word == 0 && s[i] != c)
		{
			word++;
			is_word = 1;
		}
		i++;
	}
	return (word);
}

static int	size_word(char const *s, char c)
{
	int		size_word;
	int		i;

	i = 0;
	size_word = 0;
	while (s[i] != c && s[i])
	{
		i++;
		size_word++;
	}
	return (size_word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen(s) == 0)
		return (ft_memalloc(0));
	if (!(tab = (char **)malloc(sizeof(char *) * (ft_count_world(s, c) + 1))))
		return (NULL);
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (j < ft_count_world(s, c) && s[i])
	{
		while (s[i] == c)
			i++;
		tab[j] = ft_strsub(s, i, size_word(s + i, c));
		while (s[i] != c)
			i++;
		j++;
	}
	tab[j] = 0;
	return (tab);
}
