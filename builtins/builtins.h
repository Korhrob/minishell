#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

// External character which contains all the environments
extern char	**environ;

typedef struct s_env
{
	char			*env;
	char			*value;
	struct s_env	*next;
}	t_env;

void	cmd_pwd();
void	cmd_cd(char **args);
void	cmd_env();

#endif
