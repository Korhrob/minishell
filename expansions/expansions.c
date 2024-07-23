/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:52:53 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 19:52:56 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>

// counts the number of expansions in the pipe
static int	count_expands(char *pipe)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (pipe[i] != 0)
	{
		if ((pipe[i] == '$') && (pipe[i - 1] != '$' || pipe[i + 1] != '$'))
			count++;
		flag ^= (pipe[i] == '\"');
		if (pipe[i] == '\'' && flag == 0)
		{
			i++;
			while (pipe[i] != '\'')
				i++;
		}
		i++;
	}
	return (count);
}

static int	check_extra(char *pipe)
{
	int	i;
	int	count;

	i = 0;
	count = count_expands(pipe);
	while (count > 0)
	{
		if ((pipe[i] == '$') && (pipe[i - 1] != '$' || pipe[i + 1] != '$'))
			count--;
		i++;
	}
	while (ft_isalnum(pipe[i]) || pipe[i] == '_')
		i++;
	if (pipe[i] == 0)
		return (0);
	else
		return (1);
}

// base logic behind expanding the pipes
static char	*expand_logic(char *pipe, t_env **environ, t_runtime *runtime)
{
	char	**splitpipe;
	char	*ret;
	int		count;
	int		extra;

	extra = 0;
	count = count_expands(pipe);
	splitpipe = (char **)ft_calloc(
			(sizeof(char *)),
			4 * (count * 2 + check_extra(pipe + 1) + 1));
	if (!splitpipe)
		return (NULL);
	extra += create_strings(splitpipe, pipe + 1, environ, runtime);
	if (!splitpipe)
		return (NULL);
	ret = array_join_c(splitpipe, (count * 2) + extra);
	if (!ret)
		return (NULL);
	free (pipe);
	free_expands(splitpipe, 0);
	return (ret);
}

// iterates every single pipe string and expands $ signs with environments
int	expand_dollars(char **pipes, t_env **environ, t_runtime *runtime)
{
	char	*temp;
	int		i;

	i = 0;
	while (pipes[i] != NULL)
	{
		printf("pipe = [%s]", pipes[i]);
		temp = ft_strjoin(" ", pipes[i]);
		if (!temp)
			return (MALLOC_FAIL);
		if (count_expands(temp) > 0)
		{
			free(pipes[i]);
			pipes[i] = expand_logic(temp, environ, runtime);
		}
		else
			free(temp);
		if (!pipes[i])
			return (MALLOC_FAIL);
		i++;
	}
	return (SUCCESS);
}
