/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:40:40 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:46:22 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// return start of next word
static char	*ft_next_word(const char *str, char c)
{
	while (*str != 0)
	{
		while (*str != 0 && *str == c)
			str++;
		if (str == 0)
			return (NULL);
		while (*str != 0 && *str != c)
		{
			if (*str == '\'' || *str == '\"')
				str += ft_strlen_t(str, *str);
			else
				str++;
		}
		while (*str != 0 && *str == c)
			str++;
		return ((char *)str);
	}
	return (NULL);
}

static int	ft_word_count(const char *str, char c)
{
	char	*ptr;
	int		count;

	count = -1;
	ptr = (char *)str;
	while (ptr != 0)
	{
		count++;
		ptr = (char *)ft_next_word(ptr, c);
	}
	return (count);
}

// return a copy of the current word
// flag 0 keeps the quotes
// flag 1 trims outer quotes
static char	*ft_word(const char *s, char c, int flag)
{
	char	*word;
	char	*trim;
	int		len;

	len = ft_next_word(s, c) - s;
	while (s[len -1] == c)
		len--;
	if (len < 0)
		return (NULL);
	word = (char *) ft_calloc(1, len + 1);
	if (word == 0)
		return (0);
	ft_strlcpy(word, s, len + 1);
	if (flag == 1 && ft_quote_check(word))
	{
		trim = ft_strtrim_quote(word);
		if (trim != NULL)
		{
			free(word);
			return (trim);
		}
	}
	return (word);
}

// free array and its contents
static void	*ft_clean(char **arr, int cur)
{
	while (cur >= 0)
	{
		free(arr[cur]);
		cur--;
	}
	free(arr);
	return (0);
}

/// @brief Split string s into an array, seperated by delimiter c, 
/// while respecting quotation
/// @param s input string
/// @param c delimiter
/// @param flag 0 retain quotes, 1 trim quotes
/// @return NULL terminated string array, or NULL on failure
char	**ft_split_quotes(const char *s, char c, int flag)
{
	char	**wordarr;
	int		wordcount;
	int		count;

	if (s == NULL)
		return (NULL);
	while (*s == c)
		s++;
	wordcount = ft_word_count(s, c);
	if (wordcount <= 0)
		return (NULL);
	wordarr = ft_calloc(wordcount + 1, sizeof(char *));
	if (wordarr == NULL)
		return (NULL);
	count = 0;
	while (count < wordcount)
	{
		wordarr[count] = ft_word(s, c, flag);
		if (wordarr[count] == NULL)
			return (ft_clean(wordarr, count));
		s = ft_next_word(s, c);
		count++;
	}
	return (wordarr);
}
