#include "libft/libft.h"
#include "minishell.h"
#include "builtins/builtins.h"

// Malloc error in env creation causes the program to not start
static void	malloc_env_fail(t_env **environ, int i)
{
	if (environ[i])
		free (environ[i]);
	i--;
	while (environ[i] != NULL)
	{
		free_single_env(environ[i]);
		i--;
	}
	free(environ);
	ft_printf("idleshell: cannot create process: Not enough memory");
	exit(1); // Need to see what to free
}

// Creates the entirety of the env struct with the key and value nodes
t_env	**set_env_struct(char **envp)
{
	t_env	**env;
	t_env	*env_new;
	int		i;

	i = 0;
	env = (t_env **)malloc(sizeof(t_env *) * ft_array_len((void **)envp) + 1);
	if (!env)
		malloc_env_fail(env, i);
	while (envp[i] != NULL)
	{
		env_new = (t_env *)malloc(sizeof(t_env));
		if (!env_new)
			malloc_env_fail(env, i);
		env_new->key = NULL;
		env_new->value = NULL;
		if (create_env(envp[i], env_new) == MALLOC_FAIL)
			malloc_env_fail(env, i);
		env[i] = env_new;
		i++;
	}
	env[i] = NULL;
	return (env);
}
