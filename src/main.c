/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 05:15:41 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/31 05:18:04 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_minishell		data;
	t_env			*list;

	argc = 1;
	argv = NULL;;
	list = set_list(env);
	init_builtin_tab(&data);
	init_error_tab();
	write(STDOUT_FILENO, "\033[H\033[2J", sizeof("\033[H\033[2J") - 1);
	if (!(env[0]))
		print_error(_ENOENV);
	while (42)
	{
		init_env(&data, list);
		process(&data, &list);
		free_arg(&data.copy_env);
		ft_strdel(&data.pwd);
		free_arg(&data.bin_dirs);
		free_arg(&data.arg);
	}
	return (0);
}
