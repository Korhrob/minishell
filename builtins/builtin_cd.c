/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:30:57 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 18:30:58 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "limits.h"
#include <linux/limits.h>

// Finds the old wd
static char	*find_env(t_env **environ, char *env)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (environ[i]->key != NULL)
			if (!ft_strcmp(env, environ[i]->key))
				return (environ[i]->value);
		i++;
	}
	return (NULL);
}

static int	update_oldpwd(t_runtime *runtime, char *temp_wd)
{
	char	*temp;

	temp = ft_strjoin("OLDPWD=", temp_wd);
	if (!temp)
		return (MALLOC_FAIL);
	if (cmd_export(temp, runtime) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	free (temp);
	return (SUCCESS);
}

// Fixes the old and new wd strings in the environment
static int	correct_wd(t_runtime *runtime)
{
	char	cwd[PATH_MAX];
	char	*temp_wd;

	temp_wd = find_env(runtime->env_struct, "PWD");
	if (!temp_wd)
	{
		if (find_env(runtime->env_struct, "OLDPWD") != NULL)
			cmd_unset("OLDPWD", runtime);
		return (SUCCESS);
	}
	if (find_env(runtime->env_struct, "OLDPWD") != NULL)
		if (update_oldpwd(runtime, temp_wd) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("working directory fail");
	temp_wd = ft_strjoin("PWD=", cwd);
	if (!temp_wd)
		return (MALLOC_FAIL);
	if (cmd_export(temp_wd, runtime) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	free (temp_wd);
	return (SUCCESS);
}

// Changes to home directory
static int	home_dir(t_runtime *runtime)
{
	char	*home;

	home = find_env(runtime->env_struct, "HOME");
	if (home == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "idleshell: cd: HOME not set\n");
		return (1);
	}
	else
	{
		if (chdir(home) == 0)
		{
			if (correct_wd(runtime) == MALLOC_FAIL)
			{
				ft_printf_fd(STDERR_FILENO, "idleshell: cd: not enough memory");
				return (1);
			}
			return (0);
		}
		else
			perror("cd");
	}
	return (1);
}

// Changes working directory to the provided path
int	cmd_cd(char **args, t_runtime *runtime)
{
	if (args[1] == NULL)
		return (home_dir(runtime));
	if (chdir(args[1]) == 0)
	{
		if (correct_wd(runtime) == MALLOC_FAIL)
		{
			ft_printf_fd(STDERR_FILENO, "idleshell: cd: not enough memory");
			return (1);
		}
	}
	else
	{
		perror("cd");
		return (1);
	}
	return (0);
}
