#include "minishell.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

// process all heredocs but only retain the last one
// return 1 if all heredocs succeed
// return 0 if any heredoc fails
int	process_heredoc(char **args)
{
	int		i;
	char	*delimit;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "<<") == 0)
		{
			delimit = args[i + 1];
			if (syntax_error(delimit, 1))
				return (0);
			ft_heredoc(O_WRONLY | O_CREAT, delimit);
		}
		i++;
	}
	return (1);
}

// handle heredoc behavior
// only the last heredoc should matter
// and this function shouldnt have to return anything
void	ft_heredoc(int flag, char *delimit)
{
	int		fd;
	char	*buffer;

	fd = open(".heredoc", flag, 0777);
	if (fd == -1)
		return ;
	while (1)
	{
		buffer = readline("heredoc> ");
		if (buffer == NULL)
			break ;
		if (*buffer == 0)
			continue ;
		ft_printf_fd(fd, "%s\n", buffer);
		if (ft_strcmp(buffer, delimit) == 0)
		{
			free(buffer);
			break ;
		}
		free(buffer);
		if (g_exit_status != 0)
		{
			signal_reset();
			break ;
		}
	}
	close (fd);
}
