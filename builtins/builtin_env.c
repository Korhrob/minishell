#include "builtins.h"

void	cmd_env(t_runtime *runtime)
{
	int	i;

	i = 0;
	while (runtime->env[i] != NULL)
	{
		ft_printf("%s\n", runtime->env[i]);
		i++;
	}
}