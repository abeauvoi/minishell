#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"
# include <signal.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <pwd.h>

# define BUILTIN_CD_USAGE "cd: usage: cd [-L|-P] [dir]"

/*
** Sections : signals, core, expansions, env, check_command, list, exec_builtin,
** builtin
*/

typedef struct	s_env
{
	char	*str;
	struct s_env *next;
}				t_env;

typedef struct	s_minishell
{
	char	**bin_dirs;
	char	*pwd;
	char	*dir;
	char	**arg;
	char	**builtin;
	char	*valide_path;
	char	**copy_env;
	struct termios copy_term;
}				t_minishell;

t_minishell		g_mini;

/*
** signals
*/

int			init(struct termios *term);
void		sigtest(void);

/*
** core
*/

void			free_arg(char ***arg);
void			get_fork(t_minishell *data);
void			process(t_minishell *data, t_env **list);

/*
** expansions
*/

char			*get_tilde(char *arg, char **env);
int				get_expansions(char **arg, char **env);

/*
** env
*/

char			*_getenv(t_env *lst, const char *name, size_t len);
void			init_env(t_minishell *data, t_env *list);
void			get_dir(t_minishell *data);
void			init_builtin_tab(t_minishell *data);

/*
** check_command
*/

char			*check_access(t_minishell *data);
int				check_builtin(t_minishell *data);

/*
** list
*/

int				len_list(t_env *env);
void			list_to_tab(t_env *env, t_minishell *data);
t_env			*create_node(char *str);
void			lst_push(t_env **head, t_env *new);
t_env			*set_list(char **env);
void			lst_del(t_env **env, t_env *to_del, t_env *prev);

/*
** exec_builtin
*/
void			exec_builtin(t_minishell *data, int i, t_env **list);

/*
** builtin
*/

int				builtin_cd(t_env **env, char **args);
void			builtin_env_test(char **env);
void			builtin_setenv(t_env **env, char *name, char *content);
void			builtin_echo(char **args, size_t total_length);
void			builtin_env(t_env *env);
void			builtin_unsetenv(t_env **env, char *arg, size_t len);

#endif
