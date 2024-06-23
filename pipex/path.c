#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// find 'name' in envp
// return entire line after 'name='
static char	*get_path(char **envp, const char *name)
{
	if (!envp)
		return (NULL);
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, name, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

// try all paths in 'path' string
// returns null path if it doesnt exist
static char	*try_path(char *out, char *path)
{
	char	**path_arr;
	char	*temp;
	int		i;

	path_arr = ft_split(path, ':');
	if (!path_arr)
		return (NULL);
	i = -1;
	while (path_arr[++i] != NULL)
	{
		temp = ft_strjoin_c(path_arr[i], out, '/');
		if (access(temp, F_OK) == 0)
		{
			free(out);
			out = ft_strdup(temp);
			free(temp);
			break ;
		}
		free(temp);
	}
    ft_free_arr(path_arr);
	return (out);
}

// return path to cmd
char	*get_cmd_path(char **args, char **envp)
{
	char	*out;
    char    *path;

	out = NULL;
	path = NULL;
	if (!args || *args == NULL)
		return (NULL);
	out = ft_strdup(*args);
	if (!out)
		return (NULL);
	path = get_path(envp, "PATH");
	if (!path)
		return (out);
	out = try_path(out, path);
	if (access(out, F_OK) == -1)
	{
		free(out);
		return (NULL);
	}
	return (out);
}
