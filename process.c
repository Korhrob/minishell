#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// initialize redirections and heredoc
// also set up file flags for outfile
void	set_inout(t_process *p)
{
	int	i;

	i = 0;
	while (p->args[i] != NULL)
	{
		if (i > 0 && ft_strcmp(p->args[i], "<") == 0)
			p->infile = p->args[i - 1];
		if (p->args[i + 1] != NULL && ft_strcmp(p->args[i], ">") == 0)
		{
			p->outfile = p->args[i + 1];
			p->outflag = O_WRONLY | O_CREAT;
		}
		if (p->args[i + 1] != NULL && ft_strcmp(p->args[i], ">>") == 0)
		{
			p->outfile = p->args[i + 1];
			p->outflag = O_WRONLY | O_CREAT | O_APPEND;
		}
		if (p->args[i + 1] != NULL && ft_strcmp(p->args[i], "<<") == 0)
			p->infile = ft_strdup(".heredoc");
		i++;
	}
}

// create new process struct
t_process	*new_process(char **args)
{
	t_process	*p;

	p = (t_process *)malloc(sizeof(t_process));
	if (p == NULL)
		return (NULL);
	p->infile = NULL;
	p->inflag = O_RDONLY;
	p->outfile = NULL;
	p->outflag = 0;
	p->args = args;
	set_inout(p);
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
	free(p);
}
