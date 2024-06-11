#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static void	set_inout(t_process *process, char **args)
{
	int	i;

	(void)process;
	i = 0;
	while (args[i] != NULL)
	{
		/*
		if (ft_strcmp(args[i], "<") == 0)
		{
			if (i > 0)
				process->infile = args[i - 1];
			ft_printf("redirect in from %s\n", args[i - 1]);
		}
		*/
		if (ft_strcmp(args[i], ">") == 0)
		{
			//if (args[i + 1] != NULL)
			//	process->outfile = args[i + 1];
			ft_printf("redirect out to '%s'\n", "NULL");
		}
		i++;
	}

}

t_process	*new_process(char **args)
{
	t_process	*process;

	process = (t_process *)malloc(sizeof(t_process));
	if (process == NULL)
		return (NULL);
	set_inout(process, args);
	return (process);
}
