/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:57:28 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:49:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*cs;
	size_t				i;

	i = 0;
	cs = (const unsigned char *)s;
	while (i < n)
	{
		if (cs[i] == (unsigned char) c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
