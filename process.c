#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void set_pflag(t_process *p, t_runtime *runtime)
{
	p->pflag = 0;
	ft_printf("cur index %d\n", runtime->pipe_index);
	if (runtime->pipe_count == 1)
	{
		ft_printf("single pipe\n");
		p->pflag = PF_FIRST | PF_LAST;
	}
	else if (runtime->pipe_index == 0)
	{
		ft_printf("first pipe\n");
		p->pflag |= PF_FIRST;
	}
	else if (runtime->pipe_index < runtime->pipe_count - 1)
	{
		ft_printf("middle pipe\n");
		p->pflag = PF_MIDDLE;
	}
	else
	{
		ft_printf("last pipe\n");
		p->pflag |= PF_LAST;
	}
}

// create new process struct
t_process	*new_process(char *line, t_runtime *runtime)
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
	file_redirection(p);
	p->args = ft_split_quotes(p->line, ' ', 0);
	if (p->args == NULL)
	{
		free(p);
		return (NULL);
	}
	rebind_args(p);
	p->path = get_cmd_path(p->args, runtime->env_struct);
	set_pflag(p, runtime);
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
	if (p->path != NULL)
		free(p->path);
	ft_free_arr(p->args);
	free(p);
}
