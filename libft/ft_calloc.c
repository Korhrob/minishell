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

void	*ft_calloc_err(void)
{
	errno = ENOMEM;
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *) malloc(count * size);
	if (ptr == 0)
		return (ft_calloc_err());
	ft_bzero(ptr, count * size);
	return (ptr);
}
