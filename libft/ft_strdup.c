/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:35:52 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:18 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

// duplicate string
char	*ft_strdup(const char *s1)
{
	char	*out;
	size_t	i;

	out = malloc(ft_strlen(s1) + 1);
	if (out == 0)
		return (0);
	i = 0;
	while (s1[i] != 0)
	{
		out[i] = s1[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

// duplicate string till len
char	*ft_strldup(const char *s1, size_t start, size_t len)
{
	char	*out;
	size_t	i;

	out = malloc(len + 1);
	if (out == 0)
		return (0);
	i = 0;
	while (s1[start + i] != 0 && i < len)
	{
		out[i] = s1[start + i];
		i++;
	}
	out[i] = 0;
	return (out);
}
