#include "builtins.h"

void    cmd_echo(char **args)
{
	int i;

	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '\"')
			args[i] = minitrim(args[i], '\"');
		else
			args[i] = minitrim(args[i], '\'');
		i++;
	}
	i = 0;
	if (ft_strcmp(args[1], "-n"))
		i++;
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (ft_strcmp(args[1], "-n"))
		ft_printf("\n");
}
