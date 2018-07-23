/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 02:43:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/23 04:46:09 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		__set_errno(int n)
{
	g_errno = n;
	return (-1);
}
 void	init_error_tab(void)
{
	g_errors[_ENOENV] = "Env is missing";
	g_errors[_ENOMEM] = "Cannot allocate memory";
	g_errors[_ENAMEENV] = "setenv: Variable name must contain alphanumeric characters "
				"and must begin with a letter.";
	g_errors[_ENOHOME] = "~ : HOME unset.";
	g_errors[_ENOUSER] = "Unknown user: ";
	g_errors[_ENOVAR] = ": Undefined variable.";
	g_errors[_ENOCMD] = "minishell: command not found: ";
}

void	print_error_and_exit(int error_code)
{
	ft_putendl_fd(g_errors[error_code], 2);
	exit(EXIT_FAILURE);
}

void	print_error(int error_code)
{
	ft_putendl_fd(g_errors[error_code], 2);
}

void		print_error_first(int error_code)
{
	ft_putstr_fd(g_errors[error_code], 2);
}
