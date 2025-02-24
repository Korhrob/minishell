/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:30:48 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 18:30:49 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	existing_path(t_env **environ, char *env)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (environ[i]->key != NULL)
			if (!ft_strcmp(env, environ[i]->key))
				return (SUCCESS);
		i++;
	}
	return (FAIL);
}

// Prints all the environments that have a value
int	cmd_env(t_runtime *runtime, int fd)
{
	int	i;

	i = 0;
	if (runtime == NULL)
		return (0);
	if (runtime->env_struct == NULL)
		return (0);
	if (existing_path(runtime->env_struct, "PATH") == FAIL)
	{
		ft_printf_fd(2, "idleshell: env: No such file or directory\n");
		return (1);
	}
	while (runtime->env_struct[i] != NULL)
	{
		if (runtime->env_struct[i]->value)
		{
			ft_printf_fd(fd, "%s", runtime->env_struct[i]->key);
			ft_printf_fd(fd, "=%s\n", runtime->env_struct[i]->value);
		}
		i++;
	}
	return (0);
}
