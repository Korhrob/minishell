#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "libft/libft.h"
#include "minishell.h"

#define BULTIN_CD "cd"
#define BULTIN_ENV "env"
#define BULTIN_HELP "help"
#define BULTIN_EXIT "exit"

void	do_builtin(char *arg)
{
	if (ft_strcmp(arg, BULTIN_EXIT) == 0)
		exit(0);
	ft_printf("builtin %s\n", arg);
}

int	is_builtin(char *arg)
{
	static char	*builtin[] = {
		BULTIN_CD,
		BULTIN_ENV,
		BULTIN_HELP,
		BULTIN_EXIT,
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
		// else
		// do_command(*args);
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
