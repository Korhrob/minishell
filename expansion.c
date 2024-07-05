#include "minishell.h"
#include <stdlib.h>

static void	free_expands(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		if (array[i+1] != NULL)
			i++;
		i++;
	}
	free(array);
}

static char	*find_expansion(char *key, t_env **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strcmp(environ[i]->key, key) == 0)
			return (environ[i]->value);
		i++;
	}
	return (NULL);
}

static char	*expand(char *pipe, t_env **environ)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (ft_isalnum(pipe[i]) || pipe[i] == '-' || pipe[i] == '_')
	{
		key[i] = pipe[i];
		i++;
	}
	key[i] = 0;
	return (find_expansion(key, environ));
}

static char **create_strings(char **splitpipe, char *pipe, t_env **environ)
{
	int i;
	int len;
	char *temp;

	i = 0;
	len = 0;
	temp = pipe;
	while (*temp != 0)
	{
		if ((*temp == '$') && (*temp+1 != '$' || *temp-1 != '$'))
		{
			splitpipe[i] = ft_strldup(pipe, 0, len);
			splitpipe[i+1] = expand(temp+1, environ);
			while (ft_isalnum(*temp+1) || *temp+1 == '-' || *temp+1 == '_')
				temp++;
			i = i + 2;
			pipe = temp;
			len = -1;
		}
		len++;
		temp++;
	}
	splitpipe[i] = NULL;
	return (splitpipe);
}

static char	*expand_logic(char *pipe, t_env **environ)
{
	char **splitpipe;
	int i;
	int count;

	i = 0;
	count = 0;
	while (pipe[i] != 0)
	{
		if ((pipe[i] == '$') && (pipe[i-1] != '$' || pipe[i+1] != '$'))
			count++;
		i++;
	}
	if (count == 0)
		return (pipe);
	splitpipe = (char **)malloc(sizeof(char *)*(count * 2 + 1));
	splitpipe = create_strings(splitpipe, pipe, environ);
	free (pipe);
	pipe = ft_array_join(splitpipe);
	free_expands(splitpipe);
	// Free every second string in the array and the array
	return (pipe);
}

#include <stdio.h>

int expand_dollars(char **pipes, t_env **environ)
{
	int	i;

	i = 0;
	while (pipes[i] != NULL)
	{
		printf("string before = [%s]\n", pipes[i]);
		pipes[i] = expand_logic(pipes[i], environ);
		printf("string after = [%s]\n", pipes[i]);
		i++;
	}
	return (0);
}
