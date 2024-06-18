#ifndef MINISHELL_H
# define MINISHELL_H

# define BUILTIN_CD "cd"
# define BUILTIN_ENV "env"
# define BUILTIN_HELP "help"
# define BUILTIN_EXIT "exit"
# define BUILTIN_PWD "pwd"
# define BUILTIN_UNSET "unset"
# define BUILTIN_EXPORT "export"

extern int g_exit_status;

typedef enum e_builtin_cmd
{
	CD,
	ENV,
	HELP,
	EXIT,
	PWD,
	UNSET,
	EXPORT,

	BUILTIN_MAX
}	t_builtin_cmd;

typedef struct s_runtime
{
	char	**env;
	char	*exepath;
	char	*history;
	char	*heredoc;
}	t_runtime;

typedef struct s_process
{
	int		inflag;
	int		outflag;
	char	*infile;
	char	*outfile;
	char	**args;
}	t_process;

// history

void		record_history(char *line, t_runtime *runtime);
void		print_history(char **args, t_runtime *runtime);

// signals

void		signal_init(int flag);
void		signal_signint(int signo);
void		signal_reset(void);

// readline JANK

void		rl_replace_line(const char *str, int i);

// pipes
t_process	*new_process(char **args);
void		clean_process(t_process *p);
void		set_inout(t_process *p);
void		begin_pipe(t_process *process);
int			redirect(int pipefd[2], t_process *process);

// heredoc
void		ft_heredoc(int flag, char *delimit, t_runtime *runtime);
int			process_heredoc(char *line, t_runtime *runtime);

// parse
int 		syntax_error(char *line);

#endif