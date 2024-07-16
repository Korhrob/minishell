/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:06:12 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:12 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

// return first occurance of c or 0 if not found in the string
char	*ft_strchr(const char *s, int c)
{
	while (*s != 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *) s);
		s++;
	}
	if (*s == '\0' && (char)c == '\0')
		return ((char *)(s));
	return (NULL);
}
