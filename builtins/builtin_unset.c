#include "builtins.h"

static int	array_len(char **array)
{
	int	i;

	i = 0;
	while (*array != NULL)
	{
		i++;
		array++;
	}
	return (i);
}

void	cmd_unset(char *env, t_runtime *runtime)
{
	char	**tmparr;
	int		i;
	int		j;

	tmparr = malloc(sizeof(char*) * (array_len(runtime->env)));
	i = 0;
	j = 0;
	while (runtime->env[i] != NULL)
	{
		if (ft_strncmp(runtime->env[i], env, ft_strlen(env)) == 0)
		{
			free(runtime->env[i]);
		}
		else
		{
			tmparr[j] = runtime->env[i];
			j++;
		}
		i++;
	}
	tmparr[i] = NULL;
	free(runtime->env);
	runtime->env = tmparr;
}
