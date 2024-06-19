#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// initialize redirections and heredoc
// also set up file flags for outfile
// NOTE: should do for entire line
void	set_inout(t_process *p)
{
	char	*ptr;

	ptr = p->line;
	while (*ptr != 0)
	{
		if (ft_strncmp(ptr, "<<", 2) == 0)
		{
			// cut string from this position onwards till any syntax
			ptr += 2;
			p->infile = ft_strdup(".heredoc");
		}
		else if (ft_strncmp(ptr, ">>", 2) == 0)
		{
			// cut string from this position onwards
			ptr += 2;
			p->outfile = get_filename(ptr);
			p->outflag = O_WRONLY | O_CREAT | O_APPEND;
		}
		else if (ft_strncmp(ptr, "<", 1) == 0)
		{
			// cut string from this position onwards
			ptr++;
			p->infile = get_filename(ptr);
			p->inflag = O_RDONLY;
		}
		else if (ft_strncmp(ptr, ">", 1) == 0)
		{
			// cut string from this position onwards
			ptr++;
			p->outfile = get_filename(ptr);
			p->outflag = O_WRONLY | O_CREAT;
		}
		else
			ptr++;
	}
}

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
	p->args = ft_split_quotes(line, ' ', 0);
	// check if split failed here
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
