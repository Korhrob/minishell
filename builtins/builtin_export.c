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
		{
			i++;
			break ;
		}
		i++;
	}
	j = 0;
	while (runtime->env_struct[j] != NULL)
	{
		if (!ft_strncmp(env, runtime->env_struct[j]->key, i))
			break ;
		j++;
	}
	if (j < ft_array_len((void **)runtime->env))
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

static int	create_env(char *envp, t_env *env)
{
	char	*temp;

	temp = envp;
	while (*envp != 0)
	{
		if (*envp == '=')
		{
			envp++;
			env->value = ft_strdup(envp);
			if (!env->value)
				return (0);
			env->key = ft_strldup(temp, 0, ft_strlen_t(temp, '=') + 1);
			if (!env->key)
			{
				free (env->value);
				return (0);
			}
			return (1);
		}
		envp++;
	}
	env->key = ft_strdup(temp);
	return (1);
}

// static void	replace_env(char *env, t_runtime *runtime, int index)
// {
// 	free(runtime->env[index]);
// 	runtime->env[index] = ft_strdup(env);
// }

// Adds a string to the env array insine runtime at the end
// static void	create_env(char *env, t_runtime *runtime)
// {
// 	char	**tmparr;
// 	int		i;

// 	tmparr = malloc(sizeof(char *) * (ft_array_len(runtime->env) + 2));
// 	i = 0;
// 	while (runtime->env[i] != NULL)
// 	{
// 		tmparr[i] = runtime->env[i];
// 		i++;
// 	}
// 	tmparr[i] = ft_strdup(env);
// 	i++;
// 	tmparr[i] = NULL;
// 	free(runtime->env);
// 	runtime->env = tmparr;
// }

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

// Adds a string to the env array insine runtime at the end
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
	args++;
	while (*args != NULL)
	{
		cmd_export(*args, runtime);
		args++;
	}
}

// Add just export, that sorts alphabetically
// Add malloc checks