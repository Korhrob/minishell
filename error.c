#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

/// @brief print error msg to STDERR_FILENO
/// @param ecode our custom error code
void	print_error_msg(int ecode)
{
	if (ecode & MALLOC_FAIL)
		ft_printf_fd(STDERR_FILENO, "idleshell: malloc fail\n");
	ft_printf("error %d\n", ecode);
}