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

// Used to create envp for the new shell level
// char	**convert_environ(t_env **environ)
// {
// 	char	**envp;
// 	char	*env;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	envp = (char **)ft_calloc(sizeof(char *), (ft_array_len((void **)environ) + 1));
// 	if (!envp)
// 		return (NULL);
// 	while (environ[i] != NULL)
// 	{
// 		len = ft_strlen(environ[i]->key) + ft_strlen(environ[i]->value);
// 		env = (char *)ft_calloc(sizeof(char *), (len + 2));
// 		if (!env)
// 		{
// 			ft_free_arr(envp);
// 			return (NULL);
// 		}
// 		ft_strlcat(env, environ[i]->key, ft_strlen(environ[i]->key));
// 		env[ft_strlen(env) + 1] = '=';
// 		ft_strlcat(env, environ[i]->value, ft_strlen(environ[i]->value));
// 		i++;
// 	}
// 	return (envp);
// }

// // Converts the key and value into a string for the envp
// static char	*convert_string(t_env **environ, char **envp, int i)
// {
// 	char	*env;
// 	int		len;

// 	len = ft_strlen(environ[i]->key) + ft_strlen(environ[i]->value);
// 	env = (char *)ft_calloc(sizeof(char *), (len + 2));
// 	if (!env)
// 	{
// 		ft_free_arr(envp);
// 		return (NULL);
// 	}
// 	ft_strlcat(env, environ[i]->key, ft_strlen(environ[i]->key));
// 	env[ft_strlen(env) + 1] = '=';
// 	ft_strlcat(env, environ[i]->value, ft_strlen(environ[i]->value));
// 	envp[i] = env;
// }

// // Used to create envp for the new shell level
// char	**convert_environ(t_env **environ)
// {
// 	char	**envp;
// 	int		i;

// 	i = 0;
// 	envp = (char **)ft_calloc(sizeof(char *), (ft_array_len((void **)environ) + 1));
// 	if (!envp)
// 		return (NULL);
// 	while (environ[i] != NULL)
// 	{
// 		if (convert_string(environ, envp, i) == NULL)
// 			return (NULL);
// 		i++;
// 	}
// 	return (envp);
// }

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
	ft_printf_fd(STDERR_FILENO, "idleshell: cannot create process: Not enough memory");
	exit(1);
}

static int	add_shlvl(char *env, t_env **environ)
{
	t_env	**temp;
	t_env	*new;
	int		i;

	i = ft_array_len((void **)environ);
	temp = (t_env **)malloc(sizeof(t_env *) * (i + 2));
	if (!temp)
		return (export_malloc_fail(temp, NULL));
	i = -1;
	while (environ[++i] != NULL)
		temp[i] = environ[i];
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (export_malloc_fail(NULL, new));
	new->key = NULL;
	new->value = NULL;
	if (create_env(env, new) == MALLOC_FAIL)
		return (export_malloc_fail(NULL, new));
	temp[i] = new;
	i++;
	temp[i] = NULL;
	free(environ);
	environ = temp;
	return (SUCCESS);
}

// Finds the shell level and increments it by 1
static int	assign_shlvl(t_env **environ)
{
	char	*new_value;
	int		value;
	int		i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strcmp(environ[i]->key, "SHLVL") == 0)
		{
			value = ft_atoi(environ[i]->value) + 1;
			new_value = ft_itoa(value);
			if (!new_value)
				return (MALLOC_FAIL);
			free(environ[i]->value);
			environ[i]->value = new_value;
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

	i = 0;
	environ = (t_env **)ft_calloc(sizeof(t_env *), (ft_array_len((void **)envp) + 1));
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
	if (assign_shlvl(environ) == MALLOC_FAIL)
		malloc_env_fail(environ, i);
	return (environ);
}
