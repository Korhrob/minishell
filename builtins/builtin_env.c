#include "builtins.h"

// Prints all the environments that have a value
void	cmd_env(t_runtime *runtime)
{
	int	i;

	i = 0;
	if (runtime == NULL)
		return ;
	if (runtime->env_struct == NULL)
		return ;
	while (runtime->env_struct[i] != NULL)
	{
		if (runtime->env_struct[i]->value)
			ft_printf("%s=%s\n", runtime->env_struct[i]->key, runtime->env_struct[i]->value);
		i++;
	}
}

// Check if PATH exists, if not do error
// bash: env: No such file or directory