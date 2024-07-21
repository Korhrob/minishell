/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:39:20 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:42 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy src to dst until (dstsize - 1) or src ends and place null terminator
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize <= 0)
		return (0);
	i = 0;
	while (src[i] != 0 && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dstsize);
}

// copy src to dst until n or src ends
size_t	ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	len;

	len = 0;
	if (n <= 0)
		return (len);
	len = ft_strlen(src);
	i = 0;
	while (src[i] != 0 && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (n);
}
