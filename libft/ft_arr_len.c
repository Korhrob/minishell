#include "libft.h"

// Counts the number of strings inside an array
int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (*array != NULL)
	{
		i++;
		array++;
	}
	return (i);
}
