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

// duplicate string s1 into a new string
char	*ft_strdup(const char *s1)
{
	char	*out;
	size_t	len;

	len = ft_strlen(s1);
	out = (char *)ft_calloc(1, len + 1);
	if (out == 0)
		return (0);
	ft_strlcpy(out, s1, len + 1);
	return (out);
}

// duplicate string into a new string until length of len
char	*ft_strndup(const char *s1, size_t start, size_t len)
{
	char	*out;

	out = (char *) ft_calloc(1, len + 1);
	if (out == 0)
		return (0);
	ft_strlcpy(out, s1 + start, len + 1);
	return (out);
}
