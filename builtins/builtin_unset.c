#include "builtins.h"

// Iterates the env list and copies it into a new array, if it finds the desired deletion it doesnt copy it.
void	cmd_unset(char *env, t_runtime *runtime)
{
	char	**tmparr;
	int		i;
	int		j;

	tmparr = malloc(sizeof(char *) * (ft_array_len(runtime->env)));
	i = 0;
	j = 0;
	while (runtime->env[i] != NULL)
	{
		if (ft_strncmp(runtime->env[i], env, ft_strlen(env)) == 0)
		{
			free(runtime->env[i]);
		}
		else
		{
			tmparr[j] = runtime->env[i];
			j++;
		}
		i++;
	}
	tmparr[j] = NULL;
	free(runtime->env);
	runtime->env = tmparr;
}

// Will change name later to be inline with other builtins, this function was made to
// perform multiple arguments passed to the function
void	unset_main(char **args, t_runtime *runtime)
{
	args++;
	while (*args != NULL)
	{
		cmd_unset(*args, runtime);
		args++;
	}
}

// Need to add a malloc check and need to add a check if there is anything to remove
// Need to add checks that see if the passed env is valid