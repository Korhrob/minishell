/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 03:49:13 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/29 13:59:14 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

// write char c to fd
int	ft_print_chr(int fd, unsigned int c)
{
	return (write(fd, &c, 1));
}
