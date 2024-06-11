#include "builtins.h"

static char	*find_env(char **array, char *env)
{
	char	**temp;

	temp = array;
	while (ft_strncmp(env, *temp, ft_strlen(env)))
		temp++;
	return (*temp);
}

static void	correct_wd(t_runtime *runtime)
{
	char	*temp;

	temp = find_env(runtime->env, "PWD");
}

// Changes working directory to the provided path
void	cmd_cd(char **args, t_runtime *runtime)
{
	if (chdir(args[1]) == 0)
	{
		correct_wd(runtime);
		cmd_pwd(); // Showing current directory after changing, remove later
	}
	else
	{
		ft_printf("cd did not work\n"); // Replace with perror later
	}
}

// Add functionality to just do cd to go to home directory