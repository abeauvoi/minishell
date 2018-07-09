#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 7

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

t_env			*create_node(char *str);
void			lst_push(t_env **head, t_env *new);
t_env			*set_list(t_minishell *data);
void			exec_builtin(t_minishell *data, int i, t_env **list);
void			builtin_setenv(t_env **env, char *name, char *content);
void			builtin_echo(char **args, size_t total_length);
void			builtin_env(t_env *env);
void			init_builtin_tab(t_minishell *data);
int				check_builtin(t_minishell *data);
void			get_fork(t_minishell *data);
char			*check_path(t_minishell *data);
void			get_env(char **env, t_minishell *data);
void			tab_path(char **env, t_minishell *data);
t_minishell		*init_struct(t_minishell *data);
char			*str_path(char **env);
int				get_next_line(int fd, char **line);
void			get_dir(t_minishell *data);
void			process(t_minishell *data, t_env **list);

#endif
