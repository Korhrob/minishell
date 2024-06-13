#include "minishell.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

// handle heredoc behavior
// NOTE: does not replicate linux behaviour, check bash
// heredock should open immediately, not when child is being processed
char	*ft_heredoc(int flag, char *delimit)
{
	int		fd;
	char	*buffer;

	fd = open(".heredoc", flag, 0777);
	if (fd == -1)
		return (NULL);
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
	return (".heredoc");
}
