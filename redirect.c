
#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int	in_heredoc(t_process *p, char *line)
{
	(void)line;
	if (p->infile != NULL)
		free(p->infile);
	p->infile = ft_strdup(".heredoc");
	ft_printf("set in %s\n", ".heredoc");
	return (2);
}

static int	in_file(t_process *p, char *line)
{
	if (p->infile != NULL)
		free(p->infile);
	p->infile = get_filename(line);
	p->inflag = O_RDONLY;
	ft_printf("set in %s\n", p->infile);
	return (1);
}

static int	out_file_append(t_process *p, char *line)
{
	if (p->infile != NULL)
		free(p->outfile);
	p->outfile = get_filename(line);
	p->outflag = O_WRONLY | O_CREAT | O_APPEND;
	ft_printf("set out %s\n", p->outfile);
	return (2);
}

static int	out_file(t_process *p, char *line)
{
	if (p->infile != NULL)
		free(p->outfile);
	p->outfile = get_filename(line);
	p->outflag = O_WRONLY | O_CREAT;
	ft_printf("set out %s\n", p->outfile);
	return (1);
}

// initialize redirections and heredoc
// also set up file flags for outfile
void	set_inout(t_process *p)
{
	char	*ptr;

	ptr = p->line;
	while (*ptr != 0)
	{
		if (ft_strncmp(ptr, "<<", 2) == 0)
			ptr += in_heredoc(p, ptr + 2);
		else if (ft_strncmp(ptr, ">>", 2) == 0)
			ptr += out_file_append(p, ptr + 2);
		else if (ft_strncmp(ptr, "<", 1) == 0)
			ptr += in_file(p, ptr + 1);
		else if (ft_strncmp(ptr, ">", 1) == 0)
			ptr += out_file(p, ptr + 1);
		else
			ptr++;
	}
}
