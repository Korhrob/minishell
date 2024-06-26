#include "builtins.h"

// Used in export with no arguments to print all the environments
// even without value
static void	cmd_export_info(t_runtime *runtime)
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
static int	add_env(char *env, t_runtime *runtime)
{
	t_env	**temp;
	t_env	*new;
	int		i;

	i = ft_array_len((void **)runtime->env_struct);
	temp = (t_env **)malloc(sizeof(t_env *) * i + 2);
	if (!temp)
		return (export_malloc_fail(temp, NULL));
	i = -1;
	while (runtime->env_struct[++i] != NULL)
		temp[i] = runtime->env_struct[i];
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
	free(runtime->env_struct);
	runtime->env_struct = temp;
	return (SUCCESS);
}

// Adds a string to the env struct inside runtime at the end, checks if it needs
// to be replaced or created as new
int	cmd_export(char *env, t_runtime *runtime)
{
	t_env	*temp_env;
	int		old_i;

	if (env[0] == '\"')
		env = minitrim(env, '\"');
	else
		env = minitrim(env, '\'');
	old_i = env_index_finder(env, runtime);
	if (old_i > -1)
	{
		temp_env = (t_env *)malloc(sizeof(t_env));
		if (!temp_env)
			return (export_malloc_fail(NULL, temp_env));
		temp_env->key = NULL;
		temp_env->value = NULL;
		if (create_env(env, temp_env) == MALLOC_FAIL)
			return (export_malloc_fail(NULL, temp_env));
		free_single_env(runtime->env_struct[old_i]);
		runtime->env_struct[old_i] = temp_env;
		return (SUCCESS);
	}
	add_env(env, runtime);
	return (SUCCESS);
}

// Will change name later to be inline with other builtins, this function was made to
// perform multiple arguments passed to the function
void	export_main(char **args, t_runtime *runtime)
{
	if (!args[1])
	{
		cmd_export_info(runtime);
		return ;
	}
	args++;
	while (*args != NULL)
	{
		if (cmd_export(*args, runtime) == MALLOC_FAIL)
			{
				ft_printf("idleshell: export: not enough memory\n");
				return ;
			}
		args++;
	}
	runtime->err_num = SUCCESS;
}

// Add quotation character remover