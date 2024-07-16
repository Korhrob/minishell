/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:56:36 by avegis            #+#    #+#             */
/*   Updated: 2024/07/14 19:56:38 by avegis           ###   ########.fr       */
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
char	*array_join_c(char **array, int count)
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

// free every second string in the array starting with first
void	*free_expands(char **array, int index)
{
	int	i;

	i = 0;
	if (index > 0)
		array[index] = NULL;
	while (array[i] != NULL)
	{
		free (array[i]);
		if (array[i + 1] != NULL)
			i++;
		i++;
	}
	free(array);
	return (NULL);
}
