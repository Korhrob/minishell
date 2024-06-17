#include "minishell.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>


// save str from current position till space or |
static char	*get_delimiter(char *line)
{
	char	*delimit;
	int		i;
	int		j;

	j = 0;
	while (line[j] != 0 && line[j] != ' ' && line[j] != '|')
		j++;
	delimit = (char *)malloc(j);
	if (delimit == NULL)
		return (NULL);
	i = 0;
	while (i < j)
	{
		delimit[i] = line[i];
		i++;
	}
	delimit[i] = 0;
	return (delimit);
}


// process all heredocs but only retain the last one
// return 1 if all heredocs succeed
// return 0 if any heredoc fails
int	process_heredoc(char *line, t_runtime *runtime)
{
	char	*delimiter;

	while (*line != 0)
	{
		if (ft_strncmp(line, "<<", 2) == 0)
		{
			line += 2;
			delimiter = get_delimiter(line);
			//ft_printf("\ndelimiter '%s'", delimiter);
			if (delimiter == NULL)
				return (0);
			ft_heredoc(O_WRONLY | O_CREAT, delimiter, runtime);
			free(delimiter);
		}
		line++;
	}
	return (1);
}

// handle heredoc behavior
// only the last heredoc should matter
// and this function shouldnt have to return anything
void	ft_heredoc(int flag, char *delimit, t_runtime *runtime)
{
	int		fd;
	char	*buffer;

	fd = open(runtime->heredoc, flag, 0777);
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
