/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 23:26:13 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/09 05:18:20 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		len_arg(char **arg)
{
	int		len;
	int		i;

	i = 1;
	len = 0;
	while (arg[i])
	{
		len += ft_strlen(arg[i]);
		i++;
	}
	return (len + i);
}

void	exec_builtin(t_minishell *data, int i, t_env **list)
{
	int		len;

	if (i == 0)
	{
		len = len_arg(data->arg);
		builtin_echo(data->arg + 1, len);
	}
	//else if (i == 1)
	//	builtin_cd(data->arg);
	if (i == 2)
		builtin_env(*list);
	//else if (i == 3)
	//	builtin_unsetenv(data->copy_env);
	else if (i == 4)
	{
		if (data->arg[1])
			builtin_setenv(list, data->arg[1], data->arg[2]);
		else
			builtin_env(*list);;
	}
	else if (i == 5)
		exit(EXIT_SUCCESS);
}