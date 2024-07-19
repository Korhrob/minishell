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

// clean tmp folder
static void	clean_tmp(t_runtime *runtime)
{
	if (runtime->history && access(runtime->history, F_OK))
		unlink(runtime->history);
}

//Initialization of runtime and all the possible content it may have
static void	init_runtime(t_runtime *runtime, char **envp)
{
	ft_memset(runtime, 0, sizeof(t_runtime));
	runtime->envp = envp;
	runtime->env_struct = set_env_struct(envp);
	runtime->exepath = str_pwd();
	if (runtime->exepath)
	{
		runtime->history = ft_strjoin(runtime->exepath, "/.tmp/.history");
		runtime->heredoc = ft_strjoin(runtime->exepath, "/.tmp/.heredoc");
	}
	clean_tmp(runtime);
}

static void	free_runtime(t_runtime *runtime)
{
	clean_tmp(runtime);
	if (runtime->env_struct)
		free_env(runtime->env_struct);
	if (runtime->exepath)
		free(runtime->exepath);
	if (runtime->history)
		free(runtime->history);
	if (runtime->heredoc)
		free(runtime->heredoc);
}

// exectue all builtin commands here
// should return int back to main
int	do_builtin(t_process *p, int cmd, t_runtime *runtime, int fd)
{
	if (cmd == EXIT)
		return (1);
	else if (cmd == PWD)
		cmd_pwd(fd);
	else if (cmd == CD)
		cmd_cd(p->args, runtime);
	else if (cmd == ENV)
		cmd_env(runtime, fd);
	else if (cmd == UNSET)
		unset_main(p->args, runtime);
	else if (cmd == EXPORT)
		export_main(p->args, runtime, fd);
	else if (cmd == ECHO)
		cmd_echo(p->args, fd);
	else if (cmd == HISTORY)
		print_history((p->args + 1), runtime, fd);
	return (-1);
}

// gets and returns enum if current string is builtin command
int	get_builtin(char *args)
{
	int			i;
	static char	*builtin[] = {
		BUILTIN_NONE,
		BUILTIN_CD,
		BUILTIN_ENV,
		BUILTIN_HELP,
		BUILTIN_EXIT,
		BUILTIN_PWD,
		BUILTIN_UNSET,
		BUILTIN_EXPORT,
		BUILTIN_ECHO,
		BUILITIN_HISTORY
	};

	if (args == NULL)
		return (0);
	i = 1;
	while (i < BUILTIN_MAX)
	{
		if (ft_strcmp(args, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

// execute single builtin in parent
static int	single_builtin(t_process *process, t_runtime *runtime)
{
	int fd;
	int	builtin;
	int	return_flag;

	fd = STDOUT_FILENO;
	return_flag = -1;
	if (process->outfile != NULL)
	{
		fd = open(process->outfile, process->outflag, 0644);
		if (fd == -1)
			return (EXIT_FAILURE);
	}
	builtin = get_builtin(process->args[0]);
	return_flag = do_builtin(process, builtin, runtime, fd);
	if (process->outfile != NULL)
		close(fd);
	return (return_flag);
}

// expand $, execute logic
int	execute_args(char **pipes, t_runtime *runtime)
{
	t_list	*list;
	int		return_flag;

	return_flag = -1;
	if (pipes == NULL)
		return (return_flag);
	if (expand_dollars(pipes, runtime->env_struct) == MALLOC_FAIL)
		return (return_flag);
	runtime->pipe_index = 0;
	runtime->pipe_count = ft_array_len((void **)pipes);
	list = create_process_list(pipes, runtime);
	if (list == NULL)
		return (return_flag);
	if (runtime->pipe_count <= 1 && get_builtin(((t_process*)list->content)->args[0]))
		return_flag = single_builtin(list->content, runtime);
	else
		pipex(list, runtime);
	clean_process_list(list);
	return (return_flag);
}

// main readline loop
static void	shell_interactive(t_runtime *runtime)
{
	char	*line;
	char	**pipes;
	int		status;
	int		syntax;

	status = -1;
	while (status == -1)
	{
		main_signals();
		line = readline("idleshell$ ");
		if (line == NULL)
			break ;
		if (*line != 0)
		{
			record_history(line, runtime);
			syntax = syntax_error(line);
			pipes = ft_split_quotes(line, '|', 0);
			if (!syntax)
				status = execute_args(pipes, runtime);
			ft_free_arr(pipes);
		}
		free(line);
	}
}

// non interactive (use argument), might not need
// static void	shell_nointeractive(char *line, t_runtime *runtime)
// {
// 	char	**pipes;

// 	main_signals();
// 	if (line == NULL)
// 		return ;
// 	if (*line == 0)
// 		return ;
// 	pipes = ft_split_quotes(line, '|', 0);
// 	if (!syntax_error(line))
// 		execute_args(pipes, runtime);
// 	ft_free_arr(pipes);
// }

int	main(int argc, char **argv, char **envp)
{
	t_runtime	runtime;

	(void)argc;
	(void)argv;
	signal_init(0);
	init_runtime(&runtime, envp);
	if (isatty(STDIN_FILENO) == 1)
	 	shell_interactive(&runtime);
	//else
	//	shell_nointeractive(argv[1], &runtime);
	free_runtime(&runtime);
	return (EXIT_SUCCESS);
}
