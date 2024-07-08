#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

// calculates the lenght of the arrays strings
static int	calculate_len(char **array, int count)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (count > 0)
	{
		len = len + ft_strlen(array[i]);
		i++;
		count--;
	}
	return (len);
}

// joins count amount of strings in an array into one string
static char	*array_join_c(char **array, int count)
{
	char	*out;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	out = (char *)malloc(calculate_len(array, count) + 1);
	if (!out)
		return (NULL);
	while (count > 0)
	{
		if (array[i])
			while (array[i][j] != 0)
				out[n++] = array[i][j++];
		i++;
		j = 0;
		count--;
		out[n] = 0;
	}
	out[n] = 0;
	return (out);
}

// free every second string in the array starting with first
static void	*free_expands(char **array, int index)
{
	int i;

	i = 0;
	if (index > 0)
		array[index] = NULL;
	while (array[i] != NULL)
	{
		free(array[i]);
		if (array[i+1] != NULL)
			i++;
		i++;
	}
	free(array);
	return (NULL);
}

// using the key finds the correct value if it exists
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

// Creates the key for which were looking for in the environ
static char	*expand(char *pipe, t_env **environ)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (ft_isalnum(pipe[i]) || pipe[i] == '-' || pipe[i] == '_')
		i++;
	key = (char *)malloc(i+1);
	ft_strlcpy(key, pipe, i+1);
	return (find_expansion(key, environ));
}

// iterates the pipe and creates an array with expandable portions
// replaced with corresponding environment values
static char **create_strings(char **splitpipe, char *pipe, t_env **environ)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (*pipe != 0)
	{
		if ((*pipe == '$') && (*pipe+1 != '$' || *pipe-1 != '$'))
		{
			splitpipe[i] = ft_strldup(pipe-len, 0, len);
			if (!splitpipe[i])
				return (free_expands(splitpipe, i));
			splitpipe[i+1] = expand(pipe+1, environ);
			while (ft_isalnum(*(pipe+1)) || *(pipe+1) == '-' || *(pipe+1) == '_')
				pipe++;
			i = i + 2;;
			len = -1;
		}
		len++;
		pipe++;
	}
	splitpipe[i] = NULL;
	return (splitpipe);
}

// counts the number of expansions in the pipe
static int	count_expands(char *pipe)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (pipe[i] != 0)
	{
		if ((pipe[i] == '$') && (pipe[i-1] != '$' || pipe[i+1] != '$'))
			count++;
		i++;
	}
	return (count);
}

// base logic behind expanding the pipes
static char	*expand_logic(char *pipe, t_env **environ)
{
	char	**splitpipe;
	char	*ret;
	int		count;

	count = count_expands(pipe);
	if (count == 0)
		return (pipe);
	splitpipe = (char **)malloc(sizeof(char *)*(count * 2 + 1));
	if (!splitpipe)
		return (NULL);
	splitpipe = create_strings(splitpipe, pipe, environ);
	if (!splitpipe)
		return (NULL);
	ret = array_join_c(splitpipe, count * 2);
	if (!ret)
		return (NULL);
	free (pipe);
	free_expands(splitpipe, 0);
	return (ret);
}

// iterates every single pipe string and expands $ signs with environments
int expand_dollars(char **pipes, t_env **environ)
{
	int	i;

	i = 0;
	while (pipes[i] != NULL)
	{
		pipes[i] = expand_logic(pipes[i], environ);
		if (!pipes[i])
			return (MALLOC_FAIL);
		i++;
	}
	return (SUCCESS);
}
