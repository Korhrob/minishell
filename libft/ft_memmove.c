/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:54:40 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:48:38 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*csrc;
	unsigned char		*cdst;
	size_t				i;

	if (dst == 0 && src == 0 && len > 0)
		return (0);
	csrc = (const unsigned char *)src;
	cdst = (unsigned char *)dst;
	i = len * (cdst > csrc && csrc + len > cdst);
	if (i > 0)
	{
		while (i > 0)
		{
			i--;
			cdst[i] = csrc[i];
		}
		cdst[0] = csrc[0];
		return (dst);
	}
	while (i < len)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}
