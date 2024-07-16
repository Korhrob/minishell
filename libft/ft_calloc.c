/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:11:52 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/20 22:09:19 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <errno.h>

static void	*ft_calloc_err(void)
{
	errno = ENOMEM;
	return (NULL);
}

// allocate (count * size) and memset values to 0
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	if (total <= 0)
		return (NULL);
	ptr = (void *) malloc(total);
	if (!ptr)
		return (ft_calloc_err());
	ft_bzero(ptr, total);
	return (ptr);
}
