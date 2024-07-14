#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// find key 'name' in envp
// return value for key
static char	*get_path(t_env **envp, const char *name)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i]->key, name, 4) == 0)
			return (envp[i]->value);
		i++;
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
		if (access(temp, X_OK) == 0)
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
char	*get_cmd_path(char **args, t_env **envp)
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
	if (out && access(out, F_OK) == -1)
		return (ft_free(out));
	return (out);
}
