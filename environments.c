// Creates the entirety of the env struct with the key and value nodes
static t_env	**set_env_struct(char **envp)
{
	t_env	**env;
	t_env	*env_new;
	int		i;

	i = 0;
	env = (t_env **)malloc(sizeof(t_env *) * ft_array_len((void **)envp) + 1);
	while (envp[i] != NULL)
	{
		env_new = (t_env *)malloc(sizeof(t_env));
		env_new->key = NULL;
		env_new->value = NULL;
		if (create_env(envp[i], env_new) != 1)
		{
			//do malloc check
		}
		env[i] = env_new;
		i++;
	}
	env[i] = NULL;
	return (env);
}