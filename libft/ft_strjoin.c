/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:38:28 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:24 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// join two strings
char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*out;
	unsigned int	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	out = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (out == 0)
		return (0);
	i = 0;
	while (*s1 != 0)
	{
		out[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != 0)
	{
		out[i] = *s2;
		i++;
		s2++;
	}
	out[i] = 0;
	return (out);
}

// join two strings with seperator c inbetween
char	*ft_strjoin_c(const char *s1, const char *s2, char c)
{
	char			*out;
	unsigned int	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	out = (char *) malloc(ft_strlen(s1) + 1 + ft_strlen(s2) + 1);
	if (out == 0)
		return (0);
	i = 0;
	while (*s1 != 0)
	{
		out[i] = *s1;
		i++;
		s1++;
	}
	out[i] = c;
	i++;
	while (*s2 != 0)
	{
		out[i] = *s2;
		i++;
		s2++;
	}
	out[i] = 0;
	return (out);
}
