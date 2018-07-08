#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 7

typedef struct	s_minishell
{
	char	**bin_dirs;
	char	*pwd;
	char	*dir;
	char	**arg;
	char	*valide_path;
	char	**copy_env;
}				t_minishell;

void			get_fork(t_minishell *data);
char			*check_path(t_minishell *data);
void			get_env(char **env, t_minishell *data);
void			tab_path(char **env, t_minishell *data);
t_minishell		*init_struct(t_minishell *data);
char			*str_path(char **env);
int				get_next_line(int fd, char **line);
void			get_dir(t_minishell *data);
void			process(t_minishell *data);

#endif
