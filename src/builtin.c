/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 05:13:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/07/10 02:06:34 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_echo(char **args, size_t total_length)
{
	char	*output;
	char	*tmp;

	if (!(output = ft_strnew(total_length)))
		;
	tmp = output;
	while (*args)
	{
		ft_strcpy(tmp, *args);
		tmp += ft_strlen(*args);
		++args;
		if (args)
			*tmp++ = ' ';
	}
	ft_putendl(output);
	ft_strdel(&output);
}

/*void		builtin_cd(const char **args)
{
}
*/
void		builtin_env(t_env *env)
{
	while (env)
	{
		ft_putendl(env->str);
		env = env->next;
	}
}

void		builtin_env_test(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

void		builtin_setenv(t_env **env, char *name, char *content)
{
	char	*tmp2;
	int		len;
	char	*tmp;
	t_env	*new;
	t_env	*ptr;

	len = ft_strlen(name);
	if (content)
	{
		tmp2 = ft_strjoin(name, "=");
		tmp = ft_strjoin(tmp2, content);
		ft_strdel(&tmp2);
	}
	else
		tmp = ft_strjoin(name, "=");
	ptr = *env;
	while (ptr->next)
	{
		if (!ft_strncmp(ptr->str, name, len))
		{
			free(ptr->str);
			ptr->str = ft_strdup(tmp);
			free(tmp);
			return ;
		}
		ptr = ptr->next;
	}
	new = create_node(tmp);
	lst_push(env, new);
	ft_strdel(&tmp);
}

//void		builtin_unsetenv()

