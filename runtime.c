/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:23:27 by avegis            #+#    #+#             */
/*   Updated: 2024/07/19 12:23:29 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtins/builtins.h"
#include <unistd.h>
#include <stdlib.h>

// clean tmp folder
static void	clean_tmp(t_runtime *runtime)
{
	if (runtime->history && !access(runtime->history, F_OK))
		unlink(runtime->history);
}

void	free_runtime(t_runtime *runtime)
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

//Initialization of runtime and all the possible content it may have
void	init_runtime(t_runtime *runtime, char **envp)
{
	ft_memset(runtime, 0, sizeof(t_runtime));
	runtime->envp = envp;
	runtime->env_struct = set_env_struct(envp);
	runtime->exepath = str_pwd();
	ft_itoa_buf(runtime->errorcode, 0);
	if (runtime->exepath)
	{
		runtime->history = ft_strjoin(runtime->exepath, "/.tmp/.history");
		runtime->heredoc = ft_strjoin(runtime->exepath, "/.tmp/.heredoc");
	}
	clean_tmp(runtime);
}
