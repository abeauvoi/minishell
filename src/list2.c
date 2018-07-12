/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 04:10:02 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/12 04:10:54 by jolabour         ###   ########.fr       */
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
