#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

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
		while (array[i][j] != 0)
			out[n++] = array[i][j++];
		i++;
		j = 0;
		count--;
		printf("Joined string = [%s]\n", array[i]);
		out[n] = 0;
		printf("string joined = [%s]\n", out);
	}
	out[n] = 0;
	return (out);
}

// free every second string in the array starting with first
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
	printf("Pipe key = [%s]\n", key);
	return (find_expansion(key, environ));
}

// iterates the pipe and creates an array with expandable portions
// replaced with corresponding environment values
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
		printf("temp = [%s]\n", temp);
		if ((*temp == '$') && (*temp+1 != '$' || *temp-1 != '$'))
		{
			printf("Pipe remainder = [%s] with len = %i\n", pipe, len);
			splitpipe[i] = ft_strldup(pipe, 0, len);
			printf("array string %i = [%s]\n", i, splitpipe[i]);
			splitpipe[i+1] = expand(temp+1, environ);
			printf("array string %i = [%s]\n", i+1, splitpipe[i+1]);
			while (ft_isalnum(*temp+1) || *temp+1 == '-' || *temp+1 == '_')
				temp++;
			printf("temp = [%s]\n", temp);
			i = i + 2;
			pipe = temp+1;
			len = -1;
			while (ft_isalnum(*pipe) || *pipe == '-' || *pipe == '_')
			{
				pipe++,
				len--;
			}
			printf("--------------------------\n");
		}
		printf("len = %i", len);
		len++;
		temp++;
	}
	splitpipe[i] = NULL;
	return (splitpipe);
}

// base logic behind expanding the pipes
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
	printf("Quantity of expansions = %i\n", count);
	if (count == 0)
		return (pipe);
	splitpipe = (char **)malloc(sizeof(char *)*(count * 2 + 1));
	splitpipe = create_strings(splitpipe, pipe, environ);
	free (pipe);
	pipe = array_join_c(splitpipe, count * 2);
	free_expands(splitpipe);
	return (pipe);
}

// iterates every single pipe string and expands $ signs with environments
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
	printf("expansion SUCCESS\n");
	return (0);
}
