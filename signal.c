#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

int	g_exit_status;

// toggles echo caret
// flag 0 = off
// flag 1 = on
void	signal_init(int flag)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	if (flag == 0)
		attributes.c_lflag &= ~ECHOCTL;
	else
		attributes.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

int	main_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	/* sigaction can fail?
	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}
	*/
	return (EXIT_SUCCESS);
}

int	child_signals(int pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (EXIT_SUCCESS);
}

int	heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (EXIT_SUCCESS);
}