#include "builtins.h"

void	cmd_env(t_runtime *runtime)
{
	int	i;

	i = 0;
	if (runtime == NULL)
		return ;
	if (runtime->env == NULL)
		return ;
	while (runtime->env[i] != NULL)
	{
		ft_printf("%s\n", runtime->env[i]);
		i++;
	}
}

// Add functionality to only print env's that have a '=' character (for export functionality)