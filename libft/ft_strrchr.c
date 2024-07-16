/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// return the last occurance of char c or 0 if not found in the string
char	*ft_strrchr(const char *s, int c)
{
	char	*d;

	d = 0;
	while (*s != 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
			d = (char *)s;
		s++;
	}
	if (*s == 0 && c == 0)
		return ((char *)s);
	return (d);
}
