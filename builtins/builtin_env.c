#include "builtins.h"

static int	existing_path(t_env **environ, char *env)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (environ[i]->key != NULL)
			if (!ft_strcmp(env, environ[i]->key))
				return (SUCCESS);
		i++;
	}
	return (FAIL);
}

// Prints all the environments that have a value
void	cmd_env(t_runtime *runtime)
{
	int	i;

	i = 0;
	if (runtime == NULL)
		return ;
	if (runtime->env_struct == NULL)
		return ;
	if (existing_path(runtime->env_struct, "PATH") == FAIL)
	{
		ft_printf("idleshell: env: No such file or directory");
		return ;
	}
	while (runtime->env_struct[i] != NULL)
	{
		if (runtime->env_struct[i]->value)
		{
			ft_printf("\033[1;31m%s\033[0m", runtime->env_struct[i]->key);
			ft_printf("=%s\n", runtime->env_struct[i]->value);
		}
		i++;
	}
	runtime->err_num = SUCCESS;
}
