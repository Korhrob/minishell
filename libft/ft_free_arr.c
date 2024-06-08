#include <stdlib.h>

// free char arr and its contents
// returns NULL
void	*ft_free_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
