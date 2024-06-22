#include "builtins.h"

// Iterates the env list and copies it into a new array, if it finds the desired deletion it doesnt copy it.
// void	cmd_unset(char *env, t_runtime *runtime)
// {
// 	char	**tmparr;
// 	int		i;
// 	int		j;

// 	tmparr = malloc(sizeof(char *) * (ft_array_len((void **)runtime->env)));
// 	i = 0;
// 	j = 0;
// 	while (runtime->env[i] != NULL)
// 	{
// 		if (ft_strncmp(runtime->env[i], env, ft_strlen(env)) == 0)
// 		{
// 			free(runtime->env[i]);
// 		}
// 		else
// 		{
// 			tmparr[j] = runtime->env[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	tmparr[j] = NULL;
// 	free(runtime->env);
// 	runtime->env = tmparr;
// }

void	cmd_unset(char *env, t_runtime *runtime)
{
	t_env	**temp;
	int		i;
	int		j;

	j = ft_array_len((void **)runtime->env_struct);
	temp = (t_env **)malloc(sizeof(t_env *) * j);
	i = 0;
	j = 0;
	while (runtime->env_struct[i] != NULL)
	{
		if (ft_strcmp(runtime->env_struct[i]->key, env))
			free_single_env(runtime->env_struct[i]);
		if (runtime->env_struct[i])
		{
			temp[j] = runtime->env_struct[i];
			j++;
		}
		i++;
	}
	temp[j] = NULL;
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