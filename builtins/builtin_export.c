#include "builtins.h"

// Trims the first and last character of a string and returns the result
char	*minitrim(char *str, char c)
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

// Adds a string to the env array insine runtime at the end
void	cmd_export(char *env, t_runtime *runtime)
{
	char	**tmparr;
	int		i;

	if (env[0] == '\"')
		env = minitrim(env, '\"');
	else
		env = minitrim(env, '\'');
	tmparr = malloc(sizeof(char *) * (ft_array_len(runtime->env) + 2));
	i = 0;
	while (runtime->env[i] != NULL)
	{
		tmparr[i] = runtime->env[i];
		i++;
	}
	tmparr[i] = ft_strdup(env);
	i++;
	tmparr[i] = NULL;
	free(runtime->env);
	runtime->env = tmparr;
}

// Add just export, that sorts alphabetically
// Add overwriting
// Add malloc checks