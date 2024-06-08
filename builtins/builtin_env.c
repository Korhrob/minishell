#include "builtins.h"

void	cmd_env()
{
	char	**env = environ;
	char	*current_env;
	char	*chr;

	while (*env != NULL)
	{
		current_env = *env;
		chr = getenv(current_env);
		ft_printf("%s\n", current_env);
		env++;
	}
}