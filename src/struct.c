#include "minishell.h"

t_minishell		*init_struct(t_minishell *data)
{
	if (!(data = malloc(sizeof(t_minishell))))
		return (NULL);
	data->path = NULL;
	return (data);
}
