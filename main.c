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


// exits program and unlinks history file
void	ft_exit(int ecode, t_runtime *runtime)
{
	unlink(runtime->history);
	unlink(runtime->heredoc);
	exit(ecode);
}

// execute all commands here
void	do_command(t_process *p, t_runtime *runtime)
{
	(void)runtime;
	if (ft_quote_check_arr(p->args) == 0)
	{
		ft_printf("idleshell: unexpected EOF\n");
		ft_exit(2, runtime);
	}
	if (ft_strcmp(*(p->args), "history") == 0)
		print_history((p->args + 1), runtime);
	else
	{
		ft_printf("do command %s\n", *(p->args)); // debug
		begin_pipe(p);
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
	else
		ft_printf("builtin %s\n", *(p->args)); // not needed
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

// expand $, execute args
int	execute_args(char **pipes, t_runtime *runtime)
{
	int			builtin;
	t_process	*process;

	while (*pipes != NULL)
	{
		// expand *pipes
		process = new_process(*pipes);
		if (process == NULL)
			return (-1);
		if (process->args[0] != NULL)
		{
			builtin = get_builtin(process->args[0]);
			if (builtin != -1)
				do_builtin(process, builtin, runtime);
			else
				do_command(process, runtime);
		}
		clean_process(process);
		pipes++;
	}
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
		if (*line == 0)
		{
			free(line);
			continue ;
		}
		record_history(line, runtime);
		pipes = ft_split_quotes(line, '|', 0);
		if (!syntax_error(line) && process_heredoc(line, runtime))
			status = execute_args(pipes, runtime);
		free(line);
		ft_free_arr(pipes);
		unlink(runtime->heredoc);
		if (status >= 0)
			exit(status);
	}
}

// probably not needed
void	shell_no_interactive(void)
{

}

// Copies the envp into the runtime struct as an array
static char	**set_env_array(char **envp)
{
	int		i;
	char	**envi;

	envi = malloc(sizeof(char *) * (ft_array_len(envp) + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		envi[i] = ft_strdup(envp[i]);
		i++;
	}
	envi[i] = NULL;
	return (envi);
}

//Initialization of runtime and all the possible content it may have
static void	init_runtime(t_runtime *runtime, char **envp)
{
	runtime->env = set_env_array(envp);
	runtime->exepath = get_cwd();
	runtime->history = ft_strjoin(runtime->exepath, "/.history");
	runtime->heredoc = ft_strjoin(runtime->exepath, "/.heredoc");
	unlink(runtime->history);
	unlink(runtime->heredoc);
}

static void	free_runtime(t_runtime *runtime)
{
	ft_free_arr(runtime->env);
	free(runtime->exepath);
	free(runtime->history);
	free(runtime->heredoc);
}

int	main(int argc, char **argv, char **envp)
{
	t_runtime	runtime;

	signal_init(0);
	signal(SIGINT, signal_signint);
	signal(SIGTERM, signal_signint);
	runtime.env = NULL;
	if (argc == 1 && argv)
		init_runtime(&runtime, envp);
	if (isatty(STDIN_FILENO) == 1)
		shell_interactive(&runtime);
	else
		shell_no_interactive();
	free_runtime(&runtime);
	return (0);
}

// should first split by pipes
// pipe split should respect quotes
// then expand env variables
// then split by spaces

// other stuff to handle
// echo 'asd | zxc' | cat
//<<a cat|cat
//infile<cat|cat>outfile

// if any pipes occur, all commands are done in child
// else if its builtin do it in parent

// should open the pipe before doing anything with children
// keep it open until all children are done
// then close pipe

// note ft_quote_check doesnt work as it should, copy from pipex