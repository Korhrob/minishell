/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:59:56 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/30 16:58:54 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

/*
* free string and set buffer flag on malloc fail
* str = temp string to be free
* buffer = pointer to static buffer s_read_buffer
* return value = null ptr
*/
void	*malloc_fail(char *str, struct s_read_buffer *buffer)
{
	free(str);
	buffer->index = -1;
	return (NULL);
}

/*
* initialize string 'output' and string 'src', if it doesn't exist
* src = pointer to source string
* add_len = length of string to be added
* return value = newly allocated string
*/
char	*init_str(char **src, int add_len)
{
	char	*temp;
	char	*output;
	int		cur_len;

	if (!*src)
	{
		temp = malloc(1);
		if (!temp)
			return (NULL);
		temp[0] = 0;
		*src = temp;
	}
	cur_len = ft_strlen(*src);
	output = malloc(cur_len + add_len + 1);
	return (output);
}

/*
* concatenate 'src' and add_len amount of 'buffer.str' to new string 'output'
* src = current output string
* buffer = pointer to static buffer s_read_buffer
* add_len = number of characters being added to new string
* return value = concatenated string
*/
char	*copy_str(char *src, struct s_read_buffer *buffer, int add_len)
{
	int		i;
	int		cur_len;
	char	*output;

	if (add_len <= 0)
		return (src);
	output = init_str(&src, add_len);
	if (!output)
		return (malloc_fail(src, buffer));
	i = 0;
	cur_len = ft_strlen(src);
	while (i < cur_len)
	{
		output[i] = src[i];
		i++;
	}
	while (i < cur_len + add_len)
	{
		output[i] = buffer->str[buffer->start + (i - cur_len)];
		i++;
	}
	output[i] = 0;
	free(src);
	return (output);
}
