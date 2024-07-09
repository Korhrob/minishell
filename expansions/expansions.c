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

// calculates the lenght of the arrays strings
static int	calculate_len(char **array, int count)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (count > 0)
	{
		len = len + ft_strlen(array[i]);
		i++;
		count--;
	}
	return (len);
}

// joins count amount of strings in an array into one string
static char	*array_join_c(char **array, int count)
{
	char	*out;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	out = (char *)malloc(calculate_len(array, count) + 1);
	if (!out)
		return (NULL);
	while (count > 0 || array[i])
	{
		if (array[i])
			while (array[i][j] != 0)
				out[n++] = array[i][j++];
		i++;
		j = 0;
		count--;
		out[n] = 0;
	}
	out[n] = 0;
	return (out);
}

// counts the number of expansions in the pipe
static int	count_expands(char *pipe)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (pipe[i] != 0)
	{
		if ((pipe[i] == '$') && (pipe[i - 1] != '$' || pipe[i + 1] != '$'))
			count++;
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
	while (ft_isalnum(pipe[i]) || pipe[i] == '-' || pipe[i] == '_')
		i++;
	if (pipe[i] == 0)
		return (0);
	else
		return (1);
}

// base logic behind expanding the pipes
static char	*expand_logic(char *pipe, t_env **environ)
{
	char	**splitpipe;
	char	*ret;
	int		count;

	count = count_expands(pipe);
	if (count == 0)
		return (pipe);
	splitpipe = (char **)malloc(sizeof(char *) * (count * 2 + check_extra(pipe) + 1));
	if (!splitpipe)
		return (NULL);
	splitpipe = create_strings(splitpipe, pipe, environ);
	if (!splitpipe)
		return (NULL);
	ret = array_join_c(splitpipe, count * 2);
	if (!ret)
		return (NULL);
	free (pipe);
	free_expands(splitpipe, 0);
	return (ret);
}

// iterates every single pipe string and expands $ signs with environments
int	expand_dollars(char **pipes, t_env **environ)
{
	int	i;

	i = 0;
	while (pipes[i] != NULL)
	{
		pipes[i] = expand_logic(pipes[i], environ);
		if (!pipes[i])
			return (MALLOC_FAIL);
		i++;
	}
	return (SUCCESS);
}
