
#include "libft/libft.h"
#include <stdlib.h>
#include "minishell.h"

// check if str is invalid
// flag 1 prints the syntax error
static int	syntax_cmp(char *str, int i, int flag)
{
	static char	*invalid[] = {
		"|",
		"<",
		"<<",
		">",
		">>"
	};

	if (ft_strcmp(str, invalid[i]) == 0)
	{
		if (flag == 1)
			ft_printf("syntax error near unexpected token '%s'\n", invalid[i]);
		return (0);
	}
	return (1);
}

// check if str is invalid
// flag 1 prints the syntax error
int	syntax_error(char *str, int flag)
{
	int			i;

	if (str == NULL)
	{
		if (flag == 1)
			ft_printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	i = 0;
	while (i < 5)
	{
		if (syntax_cmp(str, i, flag) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	validate_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (syntax_error(args[i], 0) && syntax_error(args[i + 1], 1))
			return (0);
		i++;
	}
	return (1);
}

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
