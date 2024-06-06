#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "minishell.h"

void	do_builtin(char *arg)
{
	if (ft_strcmp(arg, "exit") == 0)
		exit(0);
	ft_printf("implemented builtin %s\n", arg);
}

int	is_builtin(char *arg)
{
	static char	*builtin[] = {
		"cd",
		"env",
		"help",
		"exit"
	};
	int	i;

	i = 0;
	while (i < 4)
	{
		if (ft_strcmp(arg, builtin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_args(char **args)
{
	(void) args;
	
	while (*args != NULL)
	{
		if (is_builtin(*args))
			do_builtin(*args);
		args++;
	}
	return (-1);
}

void	shell_interactive(void)
{
	char	*line;
	char	**args;
	int		status;

	status = -1;
	while (status == -1)
	{
		line = readline("idleshell$ ");
		if (line == NULL)
			break ;
		record_history(line);
		args = ft_split_quotes(line, ' ', 0);
		status = execute_args(args);
		free(line);
		free(args);
		if (status >= 0)
			exit(status);
	}
}

// probably not needed
void	shell_no_interactive(void)
{

}

int	main(void)
{
	if (isatty(STDIN_FILENO) == 1)
		shell_interactive();
	else
		shell_no_interactive();
	return (0);
}
