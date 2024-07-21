/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

/// @brief print error msg to STDERR_FILENO
/// @param ecode our custom error code
void	print_error_msg(int ecode, t_runtime *runtime)
{
	if (ecode & MALLOC_FAIL)
		ft_printf_fd(STDERR_FILENO, "idleshell: malloc fail\n");
	else if (ecode == FILE_FAIL)
		ft_printf_fd(STDERR_FILENO, "idleshell: error opening file\n");
	else if (ecode & PIPE_FAIL)
		ft_printf_fd(STDERR_FILENO, "idleshell: initializing pipe failed\n");
	else
		ft_printf("idleshell: error code: %d\n", ecode);
	ft_itoa_buf(runtime->errorcode, EXIT_FAILURE);
}
