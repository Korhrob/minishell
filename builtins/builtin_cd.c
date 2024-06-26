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

static int	correct_wd(t_runtime *runtime)
{
	
}

// Fixes the old and new wd strings in the env
static int	correct_wd(t_runtime *runtime)
{
	char	cwd[PATH_MAX];
	char	*temp_wd;
	char	*temp_str;

	temp_str = find_env(runtime->env_struct, "PWD");
	if (temp_str == NULL)
	{
		if (find_env(runtime->env_struct, "OLDPWD") != NULL)
			if (cmd_export("OLDPWD=", runtime) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		return (SUCCESS);
	}
	if (find_env(runtime->env_struct, "OLDPWD") != NULL)
	{
		temp_wd = ft_strjoin("OLDPWD=", temp_str);
		if (!temp_wd)
			return (MALLOC_FAIL);
		cmd_export(temp_wd, runtime);
		free(temp_wd);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("working directory fail");
	temp_wd = ft_strjoin("PWD=", cwd);
	if (!temp_wd)
		return (MALLOC_FAIL);
	if (cmd_export(temp_wd, runtime) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	free(temp_wd);
	return (SUCCESS);
}

// Changes to home directory
static void	home_dir(t_runtime *runtime)
{
	char	*home;

	home = find_env(runtime->env_struct, "HOME");
	if (home == NULL)
	{
		ft_printf("idleshell: cd: HOME not set\n");
		return ;
	}
	else
	{
		if (chdir(home) == 0)
		{
			if (correct_wd(runtime) == MALLOC_FAIL)
				ft_printf("idleshell: cd: not enough memory");
		}
		else
			perror("cd");
	}
}

// Changes working directory to the provided path
void	cmd_cd(char **args, t_runtime *runtime)
{
	runtime->err_num = SUCCESS;
	if (args[1] == NULL)
	{
		home_dir(runtime);
		return ;
	}
	if (chdir(args[1]) == 0)
	{
		if (correct_wd(runtime) == MALLOC_FAIL)
			ft_printf("idleshell: cd: not enough memory");
	}
	else
		perror("cd");
}
