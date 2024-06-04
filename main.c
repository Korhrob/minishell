#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
char	*read_line(void)
{
	char	*line;

	line = NULL;
	if (get_next_line(STDIN_FILENO) == NULL)
	{
		// check signal (see feof)
		free(line);
		//perror errormsg
		exit(EXIT_FAILURE);
	}
	return (line);
}
*/

int	execute_args(char **args)
{
	static char	*builtin[] = {
		"cd",
		"env",
		"help",
		"exit"
	};
	(void) builtin;
	(void) args;
	/*
	while (args != 0)
	{
		args++;
	}
	*/
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
		//write(STDOUT_FILENO, "idleshell$ ", 11);
		line = readline("idleshell$ ");
		args = ft_split_quotes(line, ' ', 0);
		status = execute_args(args);
		free(line);
		free(args);
		if (status >= 0)
			exit(status);
	}
}


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
