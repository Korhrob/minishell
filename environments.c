/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:31:24 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 18:31:26 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include "builtins/builtins.h"

// Used to create envp for the pipex
char	**convert_environ(t_env **e)
{
	char	**envp;
	char	*env;
	int		len;
	int		i;

	i = 0;
	envp = (char **)ft_calloc(sizeof(char *), (ft_array_len((void **)e) + 1));
	if (!envp)
		return (NULL);
	while (e[i] != NULL)
	{
		len = ft_strlen(e[i]->key) + ft_strlen(e[i]->value);
		env = (char *)ft_calloc(sizeof(char *), (len + 2));
		if (!env)
		{
			ft_free_arr(envp);
			return (NULL);
		}
		ft_strncpy(env, e[i]->key, ft_strlen(e[i]->key));
		env[ft_strlen(env)] = '=';
		ft_strncpy(env + ft_strlen(env), e[i]->value, ft_strlen(e[i]->value));
		envp[i] = env;
		i++;
	}
	return (envp);
}

// Malloc error in env creation causes the program to not start
static void	malloc_env_fail(t_env **environ, int i)
{
	if (environ[i])
		free (environ[i]);
	i--;
	while (environ[i] != NULL)
	{
		free_single_env(environ[i]);
		i--;
	}
	free(environ);
	ft_printf_fd(2, "idleshell: cannot create process: Not enough memory");
	exit(1);
}

static int	add_shlvl(char *env, t_env ***environ)
{
	t_env	**temp;
	t_env	*new;
	int		i;

	i = ft_array_len((void **)*environ);
	temp = (t_env **)malloc(sizeof(t_env *) * (i + 2));
	if (!temp)
		return (export_malloc_fail(temp, NULL));
	i = -1;
	while ((*environ)[++i] != NULL)
		temp[i] = (*environ)[i];
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (export_malloc_fail(NULL, new));
	new->key = NULL;
	new->value = NULL;
	if (create_env(env, new) == MALLOC_FAIL)
		return (export_malloc_fail(NULL, new));
	temp[i] = new;
	temp[i + 1] = NULL;
	free(*environ);
	*environ = temp;
	return (SUCCESS);
}

// Finds the shell level and increments it by 1
static int	assign_shlvl(t_env ***environ)
{
	char	*new_value;
	int		value;
	int		i;

	i = 0;
	while ((*environ)[i] != NULL)
	{
		if (ft_strcmp((*environ)[i]->key, "SHLVL") == 0)
		{
			value = ft_atoi((*environ)[i]->value) + 1;
			if (value < 0)
				value = 0;
			new_value = ft_itoa(value);
			if (!new_value)
				return (MALLOC_FAIL);
			free((*environ)[i]->value);
			(*environ)[i]->value = new_value;
			return (SUCCESS);
		}
		i++;
	}
	if (add_shlvl("SHLVL=1", environ) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

// Creates the entirety of the env struct with the key and value nodes
t_env	**set_env_struct(char **envp)
{
	t_env	**environ;
	t_env	*env_new;
	int		i;

	i = ft_array_len((void **)envp);
	environ = (t_env **)ft_calloc(sizeof(t_env *), i + 1);
	i = 0;
	if (!environ)
		malloc_env_fail(environ, i);
	while (envp[i] != NULL)
	{
		env_new = (t_env *)malloc(sizeof(t_env));
		if (!env_new)
			malloc_env_fail(environ, i);
		env_new->key = NULL;
		env_new->value = NULL;
		if (create_env(envp[i], env_new) == MALLOC_FAIL)
			malloc_env_fail(environ, i);
		environ[i] = env_new;
		i++;
	}
	if (assign_shlvl(&environ) == MALLOC_FAIL)
		malloc_env_fail(environ, i);
	return (environ);
}
