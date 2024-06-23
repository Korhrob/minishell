#include "builtins.h"

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

// Trims the first and last character of a string and returns the result
static char	*minitrim(char *str, char c)
{
	char	*strlocal;

	if (str[0] != c || str[ft_strlen(str)-1] != c)
		return (str);
	if (*str == c)
		str++;
	strlocal = str;
	while (*str != 0)
		str++;
	str--;
	if (*str == c)
		*str = 0;
	return (strlocal);
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