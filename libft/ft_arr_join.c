/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:52:37 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 19:52:38 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	calculate_len(char **array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (array[i] != NULL)
	{
		len = len + ft_strlen(array[i]);
		i++;
	}
	return (len);
}

// join string in array into a single allocated string
char	*ft_array_join(char **array)
{
	char	*out;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	out = (char *)malloc(calculate_len(array) + 1);
	if (!out)
		return (NULL);
	while (array[i] != NULL)
	{
		while (array[i][j] != 0)
			out[n++] = array[i][j++];
		i++;
	}
	out[n] = 0;
	return (out);
}
