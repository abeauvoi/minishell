/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:37:00 by abeauvoi          #+#    #+#             */
/*   Updated: 2017/04/24 16:43:08 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isxdigit(int c)
{
	return ((48 <= c && c <= 57)
			|| (65 <= c && c <= 70) || (97 <= c && c <= 102) ? 1 : 0);
}
