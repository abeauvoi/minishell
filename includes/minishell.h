#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"

typedef struct	s_minishell
{
	char **path;
	char *pwd;
}				t_minishell;

void			get_env(char **env, t_minishell *data);
void			tab_path(char **env, t_minishell *data);
t_minishell		*init_struct(t_minishell *data);
char			*str_path(char **env);

#endif
