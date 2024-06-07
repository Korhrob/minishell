#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "libft/libft.h"
#include "minishell.h"

// test comment
// My changes
// execute all commands here
// should return how many args we advanced
void	do_command(char **args)
{
	if (ft_strcmp(*args, "history") == 0)
		print_history(args + 1);
	//ft_printf("do command %s\n", *args);
}

// exectue all builtin commands here
// should return how many args we advanced
void	do_builtin(char **args, int cmd)
{
	if (cmd == EXIT)
		exit(0);
	ft_printf("builtin %s\n", *args);
}

// gets and returns enum if current string is builtin command
int	get_builtin(char *args)
{
	int			i;
	static char	*builtin[] = {
		BULTIN_CD,
		BULTIN_ENV,
		BULTIN_HELP,
		BULTIN_EXIT,
	};

	i = 0;
	while (i < 4)
	{
		if (ft_strcmp(args, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// execute args 1 by 1
// TODO: do commands should advance args array if they have optional parameters
int	execute_args(char **args)
{
	int	builtin;

	(void) args;
	while (*args != NULL)
	{
		builtin = get_builtin(*args);
		if (builtin != -1)
			do_builtin(args, builtin);
		else
			do_command(args);
		args++;
	}
	return (-1);
}

// read stdin and split the line
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
