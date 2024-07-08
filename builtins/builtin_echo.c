#include "builtins.h"

// prints on standard output all strings from an array except
// the first and any -n flags that remove newline
void    cmd_echo(char **args)
{
	int i;

	i = 1;
	if (args[1])
		while (ft_strcmp(args[i], "-n") == 0)
			i++;
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (args[1])
	{
		if (ft_strcmp(args[1], "-n") != 0)
			ft_printf("\n");
	}
	else
		ft_printf("\n");
}
