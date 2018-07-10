#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"

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
}				t_minishell;

/*
** core
*/

void			free_arg(char **arg);
void			get_fork(t_minishell *data);
void			process(t_minishell *data, t_env **list);

/*
** env
*/

char			*str_path(t_env *list);
char			*get_pwd(t_env *list);
void			get_env(t_minishell *data, t_env *list);
void			get_dir(t_minishell *data);

/*
** check_command
*/

void			init_builtin_tab(t_minishell *data);
char			*check_access(t_minishell *data);
int				check_builtin(t_minishell *data);

/*
** list
*/

int				len_list(t_env *env);
void			list_to_tab(t_env *env, t_minishell **data);
t_env			*create_node(char *str);
void			lst_push(t_env **head, t_env *new);
t_env			*set_list(char **env);

/*
** exec_builtin
*/
void			exec_builtin(t_minishell *data, int i, t_env **list);

/*
** builtin
*/

void			builtin_env_test(char **env);
void			builtin_setenv(t_env **env, char *name, char *content);
void			builtin_echo(char **args, size_t total_length);
void			builtin_env(t_env *env);
t_env			**builtin_unsetenv(t_env **env, char *arg);

#endif
