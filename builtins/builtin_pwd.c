#include "builtins.h"
#include "limits.h"
#include <linux/limits.h>

// Fetches the current directory and prints it
void	cmd_pwd()
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("pwd");
}
