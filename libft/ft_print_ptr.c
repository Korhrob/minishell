/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 03:51:27 by rkorhone          #+#    #+#             */
/*   Updated: 2023/12/04 14:52:56 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

// write memory address to fd
int	ft_print_ptr(int fd, void *ptr)
{
	int	count;
	int	error;

	count = 0;
	error = 0;
	error = write(fd, "0x", 2);
	if (error < 0)
		return (-1);
	count = ft_print_hex(fd, (unsigned long)ptr, LOWERCASE, 0);
	if (count < 0)
		return (-1);
	return (error + count);
}
