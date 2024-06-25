#include "builtins.h"

// Used in export with no arguments to print all the environments
// even without value
static void	cmd_export_single(t_runtime *runtime)
{
	int	i;

	i = 0;
	if (runtime == NULL)
		return ;
	if (runtime->env_struct == NULL)
		return ;
	while (runtime->env_struct[i] != NULL)
	{
		ft_printf("declare -x %s", runtime->env_struct[i]->key);
		if (runtime->env_struct[i]->value)
			ft_printf("=%s\n", runtime->env_struct[i]->value);
		else
			ft_printf("\n");
		i++;
	}
}

// Finds the index of the env inside the array
static int	env_index_finder(char *env, t_runtime *runtime)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] != 0)
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	j = 0;
	while (runtime->env_struct[j] != NULL)
	{
		if (!ft_strncmp(env, runtime->env_struct[j]->key, i))
			break ;
		j++;
	}
	if (j < ft_array_len((void **)runtime->env_struct))
		return (j);
	return (-1);
}

// Adds a new env
static void	add_env(char *env, t_runtime *runtime)
{
	t_env	**temp;
	t_env	*new;
	int		i;

	i = ft_array_len((void **)runtime->env_struct);
	temp = (t_env **)malloc(sizeof(t_env *) * i + 2);
	i = 0;
	while (runtime->env_struct[i] != NULL)
	{
		temp[i] = runtime->env_struct[i];
		i++;
	}
	free(runtime->env_struct);
	new = (t_env *)malloc(sizeof(t_env));
	new->key = NULL;
	new->value = NULL;
	create_env(env, new);
	temp[i] = new;
	i++;
	temp[i] = NULL;
	runtime->env_struct = temp;
}

// Adds a string to the env struct inside runtime at the end, checks if it needs
// to be replaced or created as new
void	cmd_export(char *env, t_runtime *runtime)
{
	int		old_i;

	if (env[0] == '\"')
		env = minitrim(env, '\"');
	else
		env = minitrim(env, '\'');
	old_i = env_index_finder(env, runtime);
	if (old_i > -1)
	{
		free_single_env(runtime->env_struct[old_i]);
		runtime->env_struct[old_i] = (t_env *)malloc(sizeof(t_env));
		runtime->env_struct[old_i]->key = NULL;
		runtime->env_struct[old_i]->value = NULL;
		create_env(env, runtime->env_struct[old_i]);
		return ;
	}
	add_env(env, runtime);
}

// Will change name later to be inline with other builtins, this function was made to
// perform multiple arguments passed to the function
void	export_main(char **args, t_runtime *runtime)
{
	if (!args[1])
	{
		cmd_export_single(runtime);
		return ;
	}
	args++;
	while (*args != NULL)
	{
		cmd_export(*args, runtime);
		args++;
	}
}

// Add just export, that sorts alphabetically
// Add malloc checks
// Add quotation character remover