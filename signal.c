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

// handle all signals
/*
void	signal_signint(int signo)
{
	g_exit_status = signo;

	if (signo == SIGINT)
	{
		rl_replace_line("", 1);
		ft_putendl_fd("", STDOUT_FILENO);
		if (rl_on_new_line() == -1)
			exit(EXIT_FAILURE);
		rl_redisplay(); // only do this if executed in child
	}
	else if (signo == SIGTERM)
	{
		unlink(".history");
	}
	else if (signo == SIGQUIT)
	{

	}
}
*/

static void	handle_sigint(int sig)
{
	//ft_printf_fd(STDERR_FILENO, "handle sigint\n");
	(void)sig;
	rl_replace_line("", 1);
	ft_putendl_fd("", STDOUT_FILENO);
	//ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	// if (rl_on_new_line() == -1)
	// 	exit(EXIT_FAILURE);
	rl_redisplay(); // only do this line if executed in child
}

int	main_signals(void)
{
	struct sigaction	sa_sigint;

	ft_memset(&sa_sigint, 0, sizeof(struct sigaction));
	sa_sigint.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa_sigint, NULL);
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
	sigaction(SIGQUIT, &sa, NULL);
	return (EXIT_SUCCESS);
}

// heredoc
// ctrl-d works and gives EOF to heredoc, bash would complain about wrong EOF
// ctrl-d doesnt work, should close the heredoc

// heredoc might have to move in the child process