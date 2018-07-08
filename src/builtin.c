/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 05:13:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/08 06:22:05 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		builtin_echo(const char **args, size_t total_length)
{
	char	*output;
	char	*tmp;

	if (!(output = ft_strnew(total_length)))
		;
	tmp = output;
	while (args)
	{
		ft_strcpy(tmp, *args);
		tmp += ft_strlen(*args);
		++args;
		if (args)
			*tmp++ = ' ';
	}
	write(stdout, output, total_length);
}

void		builtin_cd(const char **args)
{
}

void		builtin_env(t_list *env)
{
	while (env)
	{
		ft_putstr(env->str);
		env = env->next;
	}
}

void		builtin_setenv(t_list **env, const char *name, const char *new,
		size_t new_len)
{
	while ((*env)->next)
	{
		if (!ft_strncmp(env->str, name, ft_strlen(name)))
		{
			free((*env)->str);
			(*env)->str = new;
			(*env)->len = new_len;
		}
		*env = (*env)->next;
	}
}

void		builtin_unsetenv()
