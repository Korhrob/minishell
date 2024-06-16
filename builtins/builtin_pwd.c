#include "builtins.h"

// Fetches the current directory and prints it
void	cmd_pwd()
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		ft_printf("pwd did not work\n"); // Replace with perror later
}

// Getcwd performs a malloc need to free

// return duplicate of cwd
char	*get_cwd()
{
	char	*str;
	char	cwd[4096];

	str = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		str = ft_strdup(cwd);
	return (str);
}