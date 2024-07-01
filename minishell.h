#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

# define BUILTIN_CD "cd"
# define BUILTIN_ENV "env"
# define BUILTIN_HELP "help"
# define BUILTIN_EXIT "exit"
# define BUILTIN_PWD "pwd"
# define BUILTIN_UNSET "unset"
# define BUILTIN_EXPORT "export"
# define BUILTIN_ECHO "echo"

# define READ 0
# define WRITE 1

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
	ECHO,
	BUILTIN_MAX
}	t_builtin_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_runtime
{
	t_env	**env_struct;
	int		enverr;
	int		pipe_index;
	int		pipe_count;
	char	*exepath;
	char	*history;
	char	*heredoc;
}	t_runtime;

typedef struct s_process
{
	char	**args;
	char	*line;
	char	*infile;
	char	*outfile;
	char	*path;
	int		inflag;
	int		outflag;
	int		pflag;
}	t_process;

typedef enum e_pflag
{
	PF_FIRST = 1,
	PF_MIDDLE = 2,
	PF_LAST = 4
}	t_pflag;

typedef struct s_pipe
{
	int	fd_in;
	int	fd_out;
}	t_pipe;

// history
void		record_history(char *line, t_runtime *runtime);
void		print_history(char **args, t_runtime *runtime);

// signals
void		signal_init(int flag);
void		signal_signint(int signo);
void		signal_reset(void);

// heredoc
void		ft_heredoc(int flag, char *delimit, t_runtime *runtime);
int			process_heredoc(char *line, t_runtime *runtime);

// readline
void		rl_replace_line(const char *str, int i);

// process
//t_process	*new_process(char *line, t_runtime *runtime);
//void		clean_process(t_process *process);
t_list		*create_process_list(char **pipes, t_runtime *runtime);
void 		*clean_process_list(t_list *list);

// parse
int			syntax_error(char *line);
char		*get_filename(char *str);
void		align_args(t_process *p);
int			is_charset(char c, const char *set);

// file_redirections
void		file_redirection(t_process *process);

// array_handler
void		rebind_args(t_process *p);

// pipex
void		pipex(t_list *process_list);

// pipex/path
char		*get_cmd_path(char **args, t_env **envp);

// pipex/redirect
int			redirect(int pipefd[2], t_process *process);
int 		do_redirect(int fd_in, int pipe[2], t_process *p);

// Environment

t_env	**set_env_struct(char **envp);


#endif