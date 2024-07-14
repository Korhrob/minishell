#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

void	print_error_msg(int ecode)
{
	if (ecode & MALLOC_FAIL)
		ft_printf_fd(STDERR_FILENO, "idleshell: malloc fail\n");
	ft_printf("error %d\n", ecode);
}