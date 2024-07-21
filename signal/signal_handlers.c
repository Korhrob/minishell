/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/libft.h"
#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <sys/ioctl.h>

void	handle_sigint(int sig)
{
	g_exit_status = sig;
	rl_replace_line("", 1);
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_child(int sig)
{
	g_exit_status = sig;
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	char	buf[2];

	g_exit_status = sig;
	rl_replace_line("", 0);
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
	buf[0] = 4;
	buf[1] = 0;
	ioctl(STDIN_FILENO, TIOCSTI, buf);
}
