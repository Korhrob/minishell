#include "minishell.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>


/* exact same functionality as get_filename
static char	*get_delimiter(char *line)
{
	char	*delimit;
	int		len;

	while (*line != 0 && *line == ' ')
		line++;
	len = 0;
	while (line[len] != 0)
	{
		if (ft_charset(line[len], " |<>"))
			break ;
		len++;
	}
	delimit = (char *)malloc(len + 1);
	if (delimit == NULL)
		return (NULL);
	ft_strlcpy(delimit, line, len + 1);
	return (delimit);
}
*/

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
			delimiter = get_filename(line);
			if (delimiter == NULL)
				return (0);
			ft_printf("delimiter '%s'\n", delimiter);
			ft_heredoc(O_WRONLY | O_CREAT, delimiter, runtime);
			free(delimiter);
		}
		else
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
	}
	close (fd);
}
