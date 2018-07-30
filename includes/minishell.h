/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 03:27:39 by jolabour          #+#    #+#             */
/*   Updated: 2018/07/25 07:39:39 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <pwd.h>
# include <limits.h>
# include "libft.h"

# define BUILTIN_CD_USAGE "cd: usage: cd [-L|-P] [dir]"

/*
** Sections : signals, core, expansions, env, check_command, list, exec_builtin,
** builtin, canonical
*/

/*
** The value 0 cannot be used for errno values (you test if g_errno != 0)
*/

typedef enum		e_errno_val
{
	_ENOMEM = 1,
	_ENAMETOOLONG,
	_ENOENV,
	_ENAMEENV,
	_ENOHOME,
	_ENOUSER,
	_ENOVAR,
	_ENOCMD,
	_ELOOP,
	_ENOTDIR,
	_EINVAL,
	_ENOENT,
	_ENOX,
	_ERRNO_VALUES
}					t_errno;

static t_errno		g_errno;
static const char	*g_errors[_ERRNO_VALUES];

typedef struct		s_env
{
	char			*str;
	struct s_env	*next;
}					t_env;

typedef struct		s_minishell
{
	char			input[256];
	char			**bin_dirs;
	char			*pwd;
	char			*dir;
	char			**arg;
	char			**builtin;
	char			**errors;
	char			*valide_path;
	char			**copy_env;
	struct termios	copy_term;
}					t_minishell;

t_minishell			g_mini;

/*
** signals
*/

int					init(struct termios *term);
void				sigtest(void);

/*
** errno
*/

void				init_error_tab(void);
void				print_error(int error_code);
void				print_error_and_exit(int error_code);
void				print_error_first(int error_code);
int					ft_set_errno(int n);

/*
** core
*/

void				free_arg(char ***arg);
void				get_fork(t_minishell *data);
void				process(t_minishell *data, t_env **list);

/*
** expansions
*/

int					get_expansions(char **arg, t_env *env);

/*
** env
*/

char				*ft_getenv(t_env *lst, const char *name, size_t len);
void				init_env(t_minishell *data, t_env *list);
void				get_dir(t_minishell *data);
void				init_builtin_tab(t_minishell *data);

/*
** check_command
*/

char				*check_access(t_minishell *data);
int					check_builtin(t_minishell *data);

/*
** list
*/

int					len_list(t_env *env);
void				list_to_tab(t_env *env, t_minishell *data);
t_env				*create_node(char *str);
void				lst_push(t_env **head, t_env *new);
t_env				*set_list(char **env);
void				lst_del(t_env **env, t_env *to_del, t_env *prev);

/*
** exec_builtin
*/
void				exec_builtin(t_minishell *data, int i, t_env **list);

/*
** builtin
*/

int					builtin_cd(t_env **env, char **args);
void				builtin_env_test(char **env);
void				builtin_setenv(t_env **env, char *name, char *content);
void				builtin_echo(char **args, size_t total_length);
void				builtin_env(t_env *env);
void				builtin_unsetenv(t_env **env, char *arg, size_t len);

/*
** canonical
*/

typedef struct		s_realpath
{
	char		*rpath;
	char		*rpath_limit;
	char		*dest;
	const char	*start;
	const char	*end;
	char		extra_buf[PATH_MAX];
	int			num_links;
}					t_realpath;

char				*realloc_rpath(t_realpath *vars);
char				*ft_realpath(const char *name);

#endif
