#include "libft.h"

// Counts the number of strings inside an array
int	ft_array_len(void **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (i);
	while (*array != NULL)
	{
		i++;
		array++;
	}
	return (i);
}
