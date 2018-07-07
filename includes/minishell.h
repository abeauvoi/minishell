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
	char **path;
	char *pwd;
	char *dir;
	char **arg;
}				t_minishell;

void			get_env(char **env, t_minishell *data);
void			tab_path(char **env, t_minishell *data);
t_minishell		*init_struct(t_minishell *data);
char			*str_path(char **env);
int				get_next_line(int fd, char **line);
void			get_dir(t_minishell *data);
void			process(t_minishell *data);

#endif
