#include "builtins.h"

// Used to free all of the env struct and itself
void    free_env(t_env **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        if (env[i]->key != NULL)
            free(env[i]->key);
        if (env[i]->value != NULL)
            free(env[i]->value);
        free(env[i]);
        i++;
    }
    free(env);
}

// Used to free a single env struct inside the env array
void    free_single_env(t_env *env)
{
    if (env->key != NULL)
        free(env->key);
    if (env->value != NULL)
        free(env->value);
    free(env);
}

// Creates the strings for the env struct
int create_env(char *envp, t_env *env)
{
    char    *value;
	int		i;

    i = ft_strlen(envp);
    value = ft_strchr(envp, '=');
    if (value != NULL)
    {
        i = value - envp;
        value++;
        env->value = ft_strdup(value);
        if (!env->value)
            return (0);
    }
    env->key = ft_strldup(envp, 0, i);
    if (!env->key && env->value)
    {
		free (env->value);
		return (0);
	}
    return (1);
}

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
