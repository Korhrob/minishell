
#include "libft/libft.h"
#include <stdlib.h>
#include "minishell.h"

// separates string array args with delimiter string "|"
char	**pipe_cut(char **args)
{
	char	**pipe_args;
	int		count;
	int		i;

	count = 0;
	while (args[count] != NULL)
	{
		if (ft_strcmp(args[count], "|") == 0)
			break ;
		count++;
	}
	pipe_args = malloc(sizeof(char *) * (count));
	if (pipe_args == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipe_args[i] = args[i];
		i++;
	}
	pipe_args[i] = NULL;
	return (pipe_args);
}
