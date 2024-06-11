#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

//extern int g_exit_status;

void	signal_signint(int signo)
{
	(void)signo;
	if (signo == SIGINT)
	{
		//g_exit_status = 1;
		rl_replace_line("", 1);
		ft_putendl_fd("", STDOUT_FILENO);
		if (rl_on_new_line() == -1)
			exit(EXIT_FAILURE);
		rl_redisplay();
	}
	else if (signo == SIGTERM)
	{
		unlink(".history");
	}
}
