/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:58:41 by rkorhone          #+#    #+#             */
/*   Updated: 2024/01/24 08:12:17 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
* initailize the static struct buffer once
* fd = file descriptor
* buffer = pointer to static buffer s_read_buffer
* index = current position in sting
* start = loop starting position in string
* bytes = currently read bytes
* str = string stored in buffer
*/
void	init_buffer(int fd, struct s_read_buffer *buffer)
{
	buffer->start = buffer->index;
	if (buffer->str != NULL)
		return ;
	buffer->index = 0;
	buffer->start = 0;
	buffer->bytes = 0;
	buffer->str = ft_calloc(1, BUFFER_SIZE);
	if (!buffer->str)
		return ;
	buffer->bytes = read(fd, buffer->str, BUFFER_SIZE);
	if (buffer->bytes <= 0)
	{
		free(buffer->str);
		buffer->str = NULL;
	}
}

/*
* free the static struct buffer if all bytes are read
* or if index is set to -1 on malloc fail
* also free output string if defined
* buffer = pointer to static buffer s_read_buffer
* output = pointer to output string
* return value = null ptr
*/
void	*free_buffer(struct s_read_buffer *buffer, char **output)
{
	if (buffer->index >= buffer->bytes || buffer->index == -1)
	{
		free(buffer->str);
		buffer->str = NULL;
	}
	if (output)
	{
		free(*output);
		*output = NULL;
	}
	return (NULL);
}

/*
* main read loop to get next line from file descriptor fd
* fd = file descriptor
* buffer = pointer to static buffer s_read_buffer
* output = pointer to output string
* return value = read line
*/
static char	*read_line(int fd, struct s_read_buffer *buffer, char **output)
{
	char	last_char;

	while (buffer->index < buffer->bytes)
	{
		last_char = buffer->str[buffer->index++];
		if (buffer->index >= BUFFER_SIZE)
		{
			*output = copy_str(*output, buffer, buffer->index - buffer->start);
			if (*output == NULL)
				return (free_buffer(buffer, output));
			ft_memset(buffer->str, 0, BUFFER_SIZE);
			buffer->bytes = read(fd, buffer->str, BUFFER_SIZE);
			if (buffer->bytes == -1)
				return (free_buffer(buffer, output));
			else if (buffer->bytes == 0)
				return (*output);
			buffer->index = 0;
			buffer->start = 0;
		}
		if (last_char == '\n' || buffer->str[buffer->index] == 0)
			break ;
	}
	*output = copy_str(*output, buffer, buffer->index - buffer->start);
	return (*output);
}

char	*get_next_line(int fd)
{
	static struct s_read_buffer	buffer[128];
	char						*output;

	if (fd < 0)
		return (NULL);
	output = 0;
	init_buffer(fd, &buffer[fd]);
	if (buffer[fd].str == NULL)
		return (NULL);
	output = read_line(fd, &buffer[fd], &output);
	free_buffer(&buffer[fd], 0);
	return (output);
}
