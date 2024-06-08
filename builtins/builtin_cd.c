#include "builtins.h"

// void	correct_pwd()
// {

// }

// Changes working directory to the provided path
void	cmd_cd(char **args)
{
	if (chdir(args[1]) == 0)
	{
		// correct_pwd();
		cmd_pwd(); // Showing current directory after changing, remove later
	}
	else
	{
		ft_printf("cd did not work\n"); // Replace with perror later
	}
}