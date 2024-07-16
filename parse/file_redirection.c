
#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int	in_heredoc(t_process *p, t_runtime *runtime)
{
	if (p->infile != NULL)
		free(p->infile);
	p->infile = ft_strdup(runtime->heredoc);
	if (p->infile == NULL && !(p->eflag & MALLOC_FAIL))
		p->eflag |= MALLOC_FAIL;
	p->inflag = O_RDONLY;
	p->fflag = 1;
	return (2);
}

static int	in_file(t_process *p, char *line)
{
	if (p->infile != NULL)
		free(p->infile);
	p->infile = get_filename(line);
	if (p->infile == NULL && !(p->eflag & MALLOC_FAIL))
		p->eflag |= MALLOC_FAIL;
	p->inflag = O_RDONLY;
	p->fflag = 0;
	return (1);
}

static int	out_file_append(t_process *p, char *line)
{
	if (p->infile != NULL)
		free(p->outfile);
	p->outfile = get_filename(line);
	if (p->outfile == NULL && !(p->eflag & MALLOC_FAIL))
		p->eflag |= MALLOC_FAIL;
	p->outflag = O_WRONLY | O_CREAT | O_APPEND;
	return (2);
}

static int	out_file(t_process *p, char *line)
{
	if (p->infile != NULL)
		free(p->outfile);
	p->outfile = get_filename(line);
	if (p->outfile == NULL && !(p->eflag & MALLOC_FAIL))
		p->eflag |= MALLOC_FAIL;
	p->outflag = O_WRONLY | O_CREAT | O_TRUNC;
	return (1);
}

// initialize redirections, heredoc and file flags
void	file_redirection(t_process *p, t_runtime *runtime)
{
	char	*ptr;

	ptr = p->line;
	p->fflag = 0;
	while (*ptr != 0)
	{
		if (ft_strncmp(ptr, "<<", 2) == 0)
			ptr += in_heredoc(p, runtime);
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
