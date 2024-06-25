#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// create new process struct
t_process	*new_process(char *line, t_runtime *runtime)
{
	t_process	*p;

	(void) runtime;
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
	p->path = get_cmd_path(p->args, runtime->env);
	ft_printf("path\n%s\n", p->path);
	ft_printf("args\n");
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
	if (p->path != NULL)
		free(p->path);
	ft_free_arr(p->args);
	free(p);
}
