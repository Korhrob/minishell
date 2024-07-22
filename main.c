/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "libft/libft.h"
#include "builtins/builtins.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// expand $, execute logic
static void	execute_args(char **pipes, t_runtime *runtime)
{
	t_list	*list;

	if (pipes == NULL)
		return ;
	if (expand_dollars(pipes, runtime->env_struct, runtime) == MALLOC_FAIL)
		return ;
	runtime->pipe_index = 0;
	runtime->pipe_count = ft_array_len((void **)pipes);
	list = create_process_list(pipes, runtime);
	if (list == NULL)
		return ;
	if (runtime->pipe_count <= 1
		&& get_builtin(((t_process *)list->content)->args[0]))
		single_builtin(list->content, runtime);
	else
		pipex(list, runtime);
	clean_process_list(list);
	return ;
}

// main readline loop
static void	shell_interactive(t_runtime *runtime)
{
	char	*line;
	char	**pipes;
	int		syntax;

	while (1)
	{
		main_signals();
		line = readline("idleshell$ ");
		if (line == NULL)
			break ;
		if (*line != 0)
		{
			record_history(line, runtime);
			syntax = syntax_error(line, runtime);
			pipes = ft_split_quotes(line, '|', 0);
			if (!syntax)
				execute_args(pipes, runtime);
			ft_free_arr(pipes);
		}
		free(line);
	}
	ft_printf_fd(STDOUT_FILENO, "exit\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_runtime	runtime;

	(void)argv;
	if (argc == 1)
	{
		signal_init(0);
		init_runtime(&runtime, envp);
		if (isatty(STDIN_FILENO) == 1)
			shell_interactive(&runtime);
		free_runtime(&runtime);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
