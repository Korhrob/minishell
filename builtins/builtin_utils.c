#include "builtins.h"

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

void    free_single_env(t_env *env)
{
    if (env->key != NULL)
        free(env->key);
    if (env->value != NULL)
        free(env->value);
    free(env);
}
