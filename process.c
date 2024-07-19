/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// set process flag
static void	set_pflag(t_process *p, t_runtime *runtime)
{
	p->pflag = 0;
	if (runtime->pipe_count == 1)
		p->pflag = PF_FIRST | PF_LAST;
	else if (runtime->pipe_index == 0)
		p->pflag |= PF_FIRST;
	else if (runtime->pipe_index < runtime->pipe_count - 1)
		p->pflag = PF_MIDDLE;
	else
		p->pflag |= PF_LAST;
}

// create new process struct
static t_process	*new_process(char *line, t_runtime *runtime)
{
	t_process	*p;

	p = (t_process *)ft_calloc(1, sizeof(t_process));
	if (p == NULL)
		return (NULL);
	set_pflag(p, runtime);
	p->inflag = O_RDONLY;
	p->line = line;
	file_redirection(p, runtime);
	process_heredoc(line, p, runtime);
	p->args = ft_split_quotes(line, ' ', 0);
	if (p->args)
		rebind_args(p->args, p);
	p->args = ft_strtrim_quote_arr(p->args, 1);
	p->path = get_cmd_path(p->args, runtime->env_struct);
	if (p->eflag != 0)
	{
		print_error_msg(p->eflag, runtime);
		ft_free_arr(p->args);
		return (ft_free(p));
	}
	return (p);
}

// clean process struct
static void	clean_process(t_process *p)
{
	if (p == NULL)
		return ;
	if (p->infile != NULL)
	{
		if (p->fflag == 1)
			unlink(p->infile);
		free(p->infile);
	}
	if (p->outfile != NULL)
		free(p->outfile);
	if (p->path != NULL)
		free(p->path);
	ft_free_arr(p->args);
	free(p);
}

// create and init all processes
t_list	*create_process_list(char **pipes, t_runtime *runtime)
{
	t_list		*list;
	t_list		*temp;
	t_process	*process;

	list = NULL;
	while (*pipes != NULL)
	{
		process = new_process(*pipes, runtime);
		if (process == NULL)
		{
			clean_process_list(list);
			return (NULL);
		}
		temp = ft_lstnew(process);
		if (temp == NULL)
		{
			clean_process_list(list);
			return (NULL);
		}
		ft_lstadd_back(&list, temp);
		pipes++;
		runtime->pipe_index++;
	}
	return (list);
}

// clean all processes
void	*clean_process_list(t_list *list)
{
	t_list	*cur;
	t_list	*next;

	cur = list;
	while (cur != NULL)
	{
		next = cur->next;
		clean_process(cur->content);
		free(cur);
		cur = next;
	}
	return (NULL);
}
