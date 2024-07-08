/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:30:12 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 18:30:13 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Used to free a single env struct inside the env array
void	free_single_env(t_env *env)
{
	if (env->key != NULL)
		free(env->key);
	if (env->value != NULL)
		free(env->value);
	free(env);
}

// Used to free all of the env struct and itself
void	free_env(t_env **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free_single_env(env[i]);
		i++;
	}
	free(env);
}

// Handles freeing and a return number for malloc fails in export functions
int	export_malloc_fail(t_env **array, t_env *node)
{
	if (node)
		free(node);
	if (array)
		free(array);
	return (MALLOC_FAIL);
}

// Creates the strings for the env struct
int	create_env(char *envp, t_env *env)
{
	char	*value;
	int		i;

	i = ft_strlen(envp);
	value = ft_strchr(envp, '=');
	if (value != NULL)
	{
		i = value - envp;
		value++;
		env->value = ft_strdup(value);
		if (!env->value)
		{
			free (env);
			return (MALLOC_FAIL);
		}
	}
	env->key = ft_strldup(envp, 0, i);
	if (!env->key && env->value)
	{
		free (env->value);
		free (env);
		return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

// Trims the first and last character of a string and returns the result
char	*minitrim(char *str, char c)
{
	char	*strlocal;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i < 2)
		return (str);
	if (str[0] != c || str[ft_strlen(str)-1] != c)
		return (str);
	if (*str == c)
		str++;
	strlocal = str;
	while (*str != 0)
		str++;
	str--;
	if (*str == c)
		*str = 0;
	return (strlocal);
}
