#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// create new process struct
t_process	*new_process(char *line)
{
	t_process	*p;

	p = (t_process *)malloc(sizeof(t_process));
	if (p == NULL)
		return (NULL);
	p->infile = NULL;
	p->inflag = O_RDONLY;
	p->outfile = NULL;
	p->outflag = 0;
	p->line = line;
	set_inout(p);
	p->args = ft_split_quotes(p->line, ' ', 0);
	if (p->args == NULL)
	{
		free(p);
		return (NULL);
	}
	//align_args(p);
	rebind_args(p);
	for (int i = 0; p->args[i] != NULL; i++)
		ft_printf("%s\n", p->args[i]);
	return (p);
}

// clean process struct
void	clean_process(t_process *p)
{
	if (p == NULL)
		return ;
	if (p->infile != NULL)
		free(p->infile);
	if (p->outfile != NULL)
		free(p->outfile);
	ft_free_arr(p->args);
	free(p);
}
