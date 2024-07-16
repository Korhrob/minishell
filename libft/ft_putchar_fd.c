/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:47:55 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/08 16:05:50 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// write char c into fd
void	ft_putchar_fd(char c, int fd)
{
	if (fd == 0 || fd == -1)
		return ;
	write(fd, &c, 1);
}
