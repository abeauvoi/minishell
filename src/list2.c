/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 05:15:29 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/31 05:15:37 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		lst_del(t_env **env, t_env *to_del, t_env *prev)
{
	if (*env == to_del)
		*env = to_del->next;
	else
		prev->next = to_del->next;
	free(to_del->str);
	free(to_del);
}
