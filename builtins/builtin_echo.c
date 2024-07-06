#include "builtins.h"

static void	quotation_trim(char **args)
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
}

void    cmd_echo(char **args)
{
	int i;

	i = 1;
	quotation_trim(args);
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
