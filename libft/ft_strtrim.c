/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:05:39 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:32 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//#include <unistd.h>

static int	ft_arrcmp(const char c, const char *set)
{
	while (*set != 0)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static void	ft_len(const char *s1, const char *set, int *start, int *end)
{
	while (*start < *end)
	{
		if (ft_arrcmp(s1[*start], set) == 0)
			break ;
		(*start)++;
	}
	while (*end > *start)
	{
		if (ft_arrcmp(s1[*end - 1], set) == 0)
			break ;
		(*end)--;
	}
}

// trim all characters in set from start and end of s1
char	*ft_strtrim(const char *s1, const char *set)
{
	char	*out;
	int		start;
	int		end;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	ft_len(s1, set, &start, &end);
	out = (char *) ft_calloc(1, end - start + 1);
	if (out == 0)
		return (0);
	ft_strlcpy(out, s1 + start, end - start + 1);
	return (out);
}
