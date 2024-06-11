#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

int g_exit_status;

// toggles echo caret
void	signal_init(int	flag)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	if (flag == 1)
		attributes.c_lflag &= ~ECHOCTL;
	else
		attributes.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

void	signal_signint(int signo)
{
	(void)signo;
	g_exit_status = signo;
	if (signo == SIGINT)
	{
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

void	signal_reset(void)
{
	g_exit_status = 0;
}
