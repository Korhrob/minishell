#include "builtins.h"

static int	key_exists(char *line, t_env **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strcmp(env[i]->key, line) == 0)
			return (1);
		i++;
	}
	return (0);
}

// Frees and removes a single node
// Creates a new struct and populates with the remaining env nodes
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
		if (ft_strcmp(runtime->env_struct[i]->key, env) == 0)
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
}

// Will change name later to be inline with other builtins, this function was made to
// perform multiple arguments passed to the function
void	unset_main(char **args, t_runtime *runtime)
{
	args++;
	while (*args != NULL)
	{
		if (key_exists(*args, runtime->env_struct) == 1)
			cmd_unset(*args, runtime);
		args++;
	}
}

// Need to add a malloc check and need to add a check if there is anything to remove
// Need to add checks that see if the passed env is valid