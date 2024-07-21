/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:33 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:15 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// find first occurance of needle in haystack
// until length of len, or NULL if not found
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	b;

	i = 0;
	b = 0;
	if (*needle == 0 || (haystack == 0 && len == 0))
		return ((char *) haystack);
	while (haystack[b] != 0 && b < len)
	{
		i = 0;
		while (needle[i] != 0 && haystack[b + i] != 0 && b + i < len)
		{
			if (needle[i] != haystack[b + i])
				break ;
			i++;
		}
		if (needle[i] == 0)
			return ((char *) haystack + b);
		b++;
	}
	return (0);
}
