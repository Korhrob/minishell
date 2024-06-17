
#include "libft/libft.h"
#include <stdlib.h>
#include "minishell.h"

// check if str is invalid
// flag 1 prints the syntax error
static char	*syntax_cmp(char *line)
{
	int			i;
	static char	*invalid[] = {
		"<<",
		">>",
		"|",
		"<",
		">"
		//"" // newline, might not need
	};

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(line, invalid[i], ft_strlen(invalid[i])) == 0)
			return (invalid[i]);
		i++;
	}
	return (NULL);
}

// check if str is invalid
// return 1 if syntax error is found
int	syntax_error(char *line)
{
	char	*cur;
	char	*prev;

	prev = NULL;
	while (*line != 0)
	{
		cur = syntax_cmp(line);
		if (cur != NULL && prev != NULL)
		{
			ft_printf("syntax error near unexpected token `%s'\n", cur);
			return (1);
		}
		prev = cur;
		if (cur != NULL)
			line += ft_strlen(cur);
		else
			line++;
	}
	if (prev != NULL)
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

// NOTE: not used anymore
/*
int	validate_args(char **pipes)
{
	int	i;

	i = 0;
	while (pipes[i] != NULL)
	{
		if (syntax_error(pipes[i], 0) && syntax_error(pipes[i + 1], 1))
			return (0);
		i++;
	}
	return (1);
}
*/

// separates string array args with delimiter string "|"
// not used anymore
/*
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
	pipe_args = malloc(sizeof(char *) * (count + 1));
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
*/
