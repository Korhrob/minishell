/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:05:40 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/10 14:32:59 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

// write string s and new line into fd
void	ft_putendl_fd(char *s, int fd)
{
	if (fd == 0 || fd == -1 || s == 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
