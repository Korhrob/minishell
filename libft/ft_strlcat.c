/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:41:21 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:33 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// join two strings into dst, up to dstsize len
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = 0;
	if (dst != 0)
		dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		dstlen = dstsize;
	srclen = ft_strlen(src);
	if (dstsize == 0 || dstlen >= dstsize)
		return (dstlen + srclen);
	i = dstlen;
	while (i < dstsize - 1 && src[i - dstlen] != 0)
	{
		dst[i] = src[i - dstlen];
		i++;
	}
	dst[i] = 0;
	return (dstlen + srclen);
}
