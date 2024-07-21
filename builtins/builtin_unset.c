/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:30:25 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 18:30:26 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	key_exists(char *line, t_env **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strcmp(env[i]->key, line) == SUCCESS)
			return (SUCCESS);
		i++;
	}
	return (1);
}

// Frees and removes a single node
// Creates a new struct and populates with the remaining env nodes
int	cmd_unset(char *env_line, t_runtime *runtime)
{
	t_env	**temp;
	int		i;
	int		j;

	j = ft_array_len((void **)runtime->env_struct);
	temp = (t_env **)malloc(sizeof(t_env *) * j);
	if (!temp)
		return (MALLOC_FAIL);
	i = 0;
	j = 0;
	while (runtime->env_struct[i] != NULL)
	{
		if (ft_strcmp(runtime->env_struct[i]->key, env_line) == SUCCESS)
			free_single_env(runtime->env_struct[i]);
		else if (runtime->env_struct[i])
		{
			temp[j] = runtime->env_struct[i];
			j++;
		}
		i++;
	}
	temp[j] = NULL;
	free(runtime->env_struct);
	runtime->env_struct = temp;
	return (SUCCESS);
}

// Will change name later to be inline with other builtins, this function was
// made to perform multiple arguments passed to the function
int	unset_main(char **args, t_runtime *runtime)
{
	args++;
	while (*args != NULL)
	{
		if (key_exists(*args, runtime->env_struct) == SUCCESS)
		{
			if (cmd_unset(*args, runtime) == MALLOC_FAIL)
			{
				ft_printf_fd(2, "idleshell: unset: not enough memory\n");
				return (1);
			}
		}
		args++;
	}
	return (0);
}
