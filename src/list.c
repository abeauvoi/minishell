/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 05:07:19 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/08/02 18:25:08 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			len_list(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void		list_to_tab(t_env *env, t_minishell *data)
{
	int		i;

	if (!(data->copy_env = malloc(sizeof(char *) * (len_list(env) + 1))))
		print_error(_ENOMEM, ERROR_HEADER_MINISH);
	i = 0;
	while (env)
	{
		if (!(data->copy_env[i] = ft_strdup(env->str)))
			print_error(_ENOMEM, ERROR_HEADER_MINISH);
		env = env->next;
		i++;
	}
	data->copy_env[i] = NULL;
}

t_env		*create_node(char *str)
{
	t_env	*new;

	if (!(new = malloc(sizeof(*new))) || !(new->str = ft_strdup(str)))
		return (NULL);
	new->next = NULL;
	return (new);
}

void		lst_push(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env		*set_list(char **env)
{
	t_env	*start;
	t_env	*new;
	int		i;

	start = NULL;
	i = 0;
	while (env[i])
	{
		if (!(new = create_node(env[i])))
			print_error(_ENOMEM, ERROR_HEADER_MINISH);
		lst_push(&start, new);
		i++;
	}
	return (start);
}
