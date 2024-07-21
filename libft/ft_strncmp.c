/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:08:41 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:06 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// return difference where strings s1 and s2 dont match until length of n, 
// or 0 if strings match
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	while (n > 0 && *us1 != 0 && *us2 != 0)
	{
		if (*us1 != *us2)
		{
			if (*us1 > *us2)
				return (1);
			else
				return (-1);
		}
		us1++;
		us2++;
		n--;
	}
	if (n == 0)
		return (0);
	if (*us1 != 0)
		return (1);
	if (*us2 != 0)
		return (-1);
	return (0);
}
