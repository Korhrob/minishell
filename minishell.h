#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>

# define BUILTIN_NONE "null"
# define BUILTIN_CD "cd"
# define BUILTIN_ENV "env"
# define BUILTIN_HELP "help"
# define BUILTIN_EXIT "exit"
# define BUILTIN_PWD "pwd"
# define BUILTIN_UNSET "unset"
# define BUILTIN_EXPORT "export"
# define BUILTIN_ECHO "echo"
# define BUILITIN_HISTORY "history"

#ifndef READ
# define READ 0
#endif
#ifndef WRITE
# define WRITE 1
#endif

extern volatile sig_atomic_t 	g_exit_status;

typedef enum e_builtin_cmd
{
	NONE,
	CD,
	ENV,
	HELP,
	EXIT,
	PWD,
	UNSET,
	EXPORT,
	ECHO,
	HISTORY,
	BUILTIN_MAX
}	t_builtin_cmd;

typedef enum e_error_code
{
	SUCCESS,
	FAIL,
	MALLOC_FAIL
}	t_error_code;

typedef enum e_pflag
{
	PF_FIRST = 1,
	PF_MIDDLE = 2,
	PF_LAST = 4
}	t_pflag;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_runtime
{
	t_env	**env_struct;
	int		pipe_index;
	int		pipe_count;
	int		exit_status;
	int		history_line_count;
	char	**envp;
	char	*exepath;
	char	*history;
	char	*heredoc;
}	t_runtime;

// args		= arg array
// line		= entire pipe string
// infile	= input file name
// outfile	= outfile file name
// path		= cmd path
// inflag	= input file flags
// outflag	= output file flags
// pflag	= process flag bitmask, PF_FIRST, PF_MIDDLE, PF_LAST
// fflag	= file flag, 1 = use heredoc
typedef struct s_process
{
	char	**args;
	char	*line;
	char	*infile;
	char	*outfile;
	char	*path;
	int		inflag;
	int		outflag;
	int		fflag;
	int		pflag;
}	t_process;

typedef struct s_pipe
{
	int	fd_in;
	int	fd_out;
}	t_pipe;

typedef struct s_exp
{
	int		len;
	int		i;
	char	*pipe;
}	t_exp;

typedef struct s_exp
{
	int		len;
	int		i;
	char	*pipe;
}	t_exp;

// main.c

int			get_builtin(char *args);
int			do_builtin(t_process *p, int cmd, t_runtime *runtime, int fd);

// history.c

void		record_history(char *line, t_runtime *runtime);
void		print_history(char **args, t_runtime *runtime, int fd);

// signals.c

void		signal_init(int flag);
int			main_signals(void);
int			child_signals(void);
int			heredoc_signals(void);

// heredoc.c

void		ft_heredoc(char *delimit, t_process *process);
int			process_heredoc(char *line, t_process *process, t_runtime *runtime);

// readline.h

void		rl_replace_line(const char *str, int i);

// process.c

t_list		*create_process_list(char **pipes, t_runtime *runtime);
void		*clean_process_list(t_list *list);

// parse.c

int			syntax_error(char *line);
char		*get_filename(char *str);
int			is_charset(char c, const char *set); // move to libft

// file_redirections.c

void		file_redirection(t_process *process, t_runtime *runtime);

// array_handler.c

void		rebind_args(char **args, t_process *p);

// pipex.c

void		pipex(t_list *process_list, t_runtime *runtime);

// pipex.c

char		*get_cmd_path(char **args, t_env **envp);
int			do_redirect(int fd_in, int pipe[2], t_process *p);

// environment.c

t_env		**set_env_struct(char **envp);

// expansions.c

int			expand_dollars(char **pipes, t_env **environ);
char		**create_strings(char **splitpipe, char *pipe, t_env **environ);
void		*free_expands(char **array, int index);

#endif