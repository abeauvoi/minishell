/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 02:43:02 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/08/02 18:38:28 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_set_errno(int err)
{
	g_errno = err;
	return (-1);
}

void	*ft_set_errno2(int err)
{
	g_errno = err;
	return (NULL);
}

 void	init_error_tab(void)
{
	g_errors[_ENOMEM - 1] = "Cannot allocate memory";
	g_errors[_ENOENV - 1] = "Env is missing";
	g_errors[_ENAMEENV - 1] = "Setenv: Variable name must contain alphanumeric "
		"characters and must begin with a letter.";
	g_errors[_ENOHOME - 1] = "~ : HOME unset.";
	g_errors[_ENOUSER - 1] = "Unknown user: ";
	g_errors[_ENOVAR - 1] = ": Undefined variable.";
	g_errors[_ENOCMD - 1] = "minishell: command not found: ";
	g_errors[_ENOX - 1] = "minishell: permission denied: ";
	g_errors[_ENOPWD - 1] = "PWD not set";
	g_errors[_ENOOLDPWD - 1] = "OLDPWD not set";
	g_errors[_ENOTTY - 1] = "Not a terminal, exiting";
	g_errors[_ENOCDPATH - 1] = "CDPATH not set";
	g_errors[_ENOENT - 1] = "No such file or directory";
	g_errors[_ENAMETOOLONG - 1] = "File name too long";
}

void	print_error(int err, char *header)
{
	char		buf[256];
	char		*ptr;
	const char	*msg;

	msg = g_errors[err - 1];
	if (header)
	{
		ft_strcpy(buf, header);
		ptr = buf + ft_strlen(header);
	}
	else
		ptr = buf;
	ft_strcpy(ptr, msg);
	ptr += ft_strlen(msg);
	*ptr++ = '\n';
	write(STDERR_FILENO, buf, ptr - buf);
	g_errno = 0;
	if (err == _ENOMEM || err == _ENOTTY)
		exit(EXIT_FAILURE);
}

void	print_error_first(int err)
{
	ft_putstr_fd(g_errors[err - 1], 2);
}
