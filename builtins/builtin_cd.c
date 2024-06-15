#include "builtins.h"
#include "limits.h"
#include <linux/limits.h>

// Finds the old wd
static char	*find_env(char **array, char *env)
{
	char	**temp;

	temp = array;
	while (*temp != NULL)
	{
		if (!ft_strncmp(env, *temp, ft_strlen(env)))
			break ;
		temp++;
	}
	if (temp)
		return (*temp);
	return (NULL);
}

// Fixes the old and new wd strings in the env
static void	correct_wd(t_runtime *runtime)
{
	char	cwd[PATH_MAX];
	char	*new_wd;
	char	*temp;
	char	*old_env;

	temp = find_env(runtime->env, "PWD=");
	if (temp == NULL)
	{
		if (find_env(runtime->env, "OLDPWD=") != NULL)
			cmd_export("OLDPWD=", runtime);
		return ;
	}
	if (find_env(runtime->env, "OLDPWD=") != NULL)
	{
		old_env = ft_strjoin("OLD", temp); // Handle freeing the string in export?
		cmd_export(old_env, runtime);
		free(old_env);
	}
	getcwd(cwd, sizeof(cwd));
	new_wd = ft_strjoin("PWD=", cwd); // Handle freeing the string in export?
	cmd_export(new_wd, runtime);
	free(new_wd);
}

// Changes to home directory
static void	home_dir(t_runtime *runtime)
{
	char	*home;

	home = find_env(runtime->env, "HOME=");
	if (home == NULL)
	{
		ft_printf("idleshell: cd: HOME not set\n");
		return ;
	}
	else
	{
		home+=5;
		if (chdir(home) == 0)
		{
			correct_wd(runtime);
			cmd_pwd(); // Showing current directory after changing, remove later
		}
		else
			ft_printf("cd did not work home version\n"); // Replace with perror later
	}
}

// Changes working directory to the provided path
void	cmd_cd(char **args, t_runtime *runtime)
{
	if (args[1] == NULL)
	{
		home_dir(runtime);
		return ;
	}
	if (chdir(args[1]) == 0)
	{
		correct_wd(runtime);
		cmd_pwd(); // Showing current directory after changing, remove later
	}
	else
	{
		ft_printf("cd did not work normal version\n"); // Replace with perror later
	}
}

// check cwd return value of NULL