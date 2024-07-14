#include "libft.h"
#include <stdlib.h>

static size_t	ft_trim_len(const char *str)
{
	int	i;
	size_t	len;

	i = 0;
	while (*str != 0)
	{
		if (*str == '\'' || *str == '\"')
		{
			len = ft_strlen_t(str, *str);
			if (len >= 2)
			{
				i += len - 2;
				str += len;
				continue;
			}
		}
		i++;
		str++;
	}
	return (i);
}

// trims outer quotes from str and returns a new string, should return NULL on allocation failure
// TODO: double tripple test this
char	*ft_strtrim_quote(const char *str)
{
	char	*out;
	char	*ptr;
	//char	*debug = (char *)str;
	size_t	len;

	len = ft_trim_len(str);
	out = (char *)ft_calloc(1, len + 1);
	//ft_printf_fd(STDERR_FILENO, "calloc %d + 1, size %d\n", len, sizeof(out));
	if (!out)
		return (NULL);
	ptr = out;
	while (*str != 0)
	{
		if (*str == '\'' || *str == '\"')
		{
			len = ft_strlen_t(str, *str);
			if (len >= 2)
			{
				//ft_printf_fd(STDERR_FILENO, "strncpy [%s] %d\n", str, len - 2);
				out += ft_strncpy(out, str + 1, len - 2);
				str += len;
				continue;
			}
		}
		//ft_printf_fd(STDERR_FILENO, "strncpy [%c]\n", *str);
		*out++ = *str++;
	}
	//ft_printf_fd(STDERR_FILENO, "original [%s]\ntrimmed [%s]\n\n", debug, ptr);
	return (ptr);
}

// create a copy of an array and trim paired quotes from all strings in array
// if flag is set, free the original array before returning
char	**ft_strtrim_quote_arr(char **arr, int flag)
{
	char	**out;
	int		i;

	if (arr == NULL || *arr == NULL)
		return (arr);
	out = (char **) ft_calloc(1, sizeof(arr));
	if (!out)
		return (arr);
	i = 0;
	while (arr[i])
	{
		out[i] = ft_strtrim_quote(arr[i]);
		if (!out[i])
		{
			ft_free_arr(out);
			return (arr);
		}
		i++;
	}
	if (flag)
		ft_free_arr(arr);
	return (out);
}
