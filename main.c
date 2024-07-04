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

//Initialization of runtime and all the possible content it may have
static void	init_runtime(t_runtime *runtime, char **envp)
{
	runtime->env_struct = set_env_struct(envp);
	runtime->exepath = str_pwd();
	runtime->history = ft_strjoin(runtime->exepath, "/.history");
	runtime->heredoc = ft_strjoin(runtime->exepath, "/.heredoc");
	runtime->pipe_count = 0;
	runtime->pipe_index = 0;
	unlink(runtime->history);
	unlink(runtime->heredoc);
}

static void	free_runtime(t_runtime *runtime)
{
	free_env(runtime->env_struct);
	free(runtime->exepath);
	free(runtime->history);
	free(runtime->heredoc);
}

// exits program and unlinks history file
void	ft_exit(int ecode, t_runtime *runtime)
{
	unlink(runtime->history);
	unlink(runtime->heredoc);
	free_runtime(runtime);
	exit(ecode);
}

// DEPRECATED: NO LONGER USED
void	do_command(t_process *p, t_runtime *runtime)
{
	(void)runtime;
	if (ft_quote_check_arr(p->args) == 0)
	{
		ft_printf("idleshell: unexpected EOF\n");
		ft_exit(2, runtime);
	}
}

// exectue all builtin commands here
void	do_builtin(t_process *p, int cmd, t_runtime *runtime)
{
	if (cmd == EXIT)
		ft_exit(0, runtime);
	else if (cmd == PWD)
		cmd_pwd();
	else if (cmd == CD)
		cmd_cd(p->args, runtime);
	else if (cmd == ENV)
		cmd_env(runtime);
	else if (cmd == UNSET)
		cmd_unset(p->args[1], runtime);
	else if (cmd == EXPORT)
		cmd_export(p->args[1], runtime);
	else if (cmd == ECHO)
		cmd_echo(p->args);
	else if (cmd == HISTORY)
		print_history((p->args + 1), runtime);
}

// gets and returns enum if current string is builtin command
int	get_builtin(char *args)
{
	int			i;
	static char	*builtin[] = {
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

	i = 0;
	while (i < BUILTIN_MAX)
	{
		if (ft_strcmp(args, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// execute single builtin in parent
int	single_builtin(t_process *process, t_runtime *runtime)
{
	int	builtin;

	if (runtime->pipe_count > 1)
		return (0);
	builtin = get_builtin(process->args[0]);
	if (builtin != -1)
	{
		do_builtin(process, builtin, runtime);
		return (1);
	}
	return (0);
}

// expand $, execute args
int	execute_args(char **pipes, t_runtime *runtime)
{
	t_list	*list;

	// EXPAND **pipes
	expand_dollars(pipes, runtime->env_struct);
	runtime->pipe_index = 0;
	runtime->pipe_count = ft_array_len((void **)pipes);
	list = create_process_list(pipes, runtime);
	if (list == NULL)
	{
		// MALLOC FLAG
		return (-1);
	}
	if (!single_builtin(list->content, runtime))
		pipex(list);
	clean_process_list(list);
	return (-1);
}

// read stdin and split the line
void	shell_interactive(t_runtime *runtime)
{
	char	*line;
	char	**pipes;
	int		status;

	status = -1;
	while (status == -1)
	{
		line = readline("idleshell$ ");
		if (line == NULL)
			break ;
		if (*line != 0)
		{
			record_history(line, runtime);
			pipes = ft_split_quotes(line, '|', 0);
			if (!syntax_error(line) && process_heredoc(line, runtime))
				status = execute_args(pipes, runtime);
			ft_free_arr(pipes);
			unlink(runtime->heredoc);
			if (status >= 0)
				exit(status);
			signal_reset();
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_runtime	runtime;

	signal_init(0);
	signal(SIGINT, signal_signint);
	signal(SIGTERM, signal_signint);
	if (argc == 1 && argv)
		init_runtime(&runtime, envp);
	if (isatty(STDIN_FILENO) == 1)
		shell_interactive(&runtime);
	free_runtime(&runtime);
	return (0);
}

// note ft_quote_check doesnt work as it should, 
// double check all quote related functions