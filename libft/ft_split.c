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

// return total word count seperated by c
// q'' is handled as 1 word
static int	ft_wordcount(const char *s, char c)
{
	int		count;

	count = 0;
	while (*s != 0)
	{
		while (*s == c && *s != 0)
			s++;
		count++;
		while (*s != c && *s != 0)
			s++;
	}
	return (count);
}

// return len to next word
static int	ft_nextword(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i] != 0)
		i++;
	while (s[i] == c && s[i] != 0)
		i++;
	return (i);
}

static char	*ft_word(const char *s, char c)
{
	char	*word;
	int		i;
	int		len;

	len = 0;
	while (s[len] != 0 && s[len] != c)
		len++;
	word = (char *) malloc(len + 1);
	if (word == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

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

// split the string s into allocated NULL terminated array with seperator char c
char	**ft_split(const char *s, char c)
{
	char	**wordarr;
	int		wordcount;
	int		count;

	if (s == 0)
		return (0);
	if (*s == c)
		s += ft_nextword(s, c);
	wordcount = ft_wordcount(s, c);
	wordarr = (char **) malloc((wordcount + 1) * sizeof(char *));
	if (wordarr == 0)
		return (0);
	count = 0;
	while (count < wordcount)
	{
		wordarr[count] = ft_word(s, c);
		if (wordarr[count] == 0)
			return (ft_clean(wordarr, count));
		s += ft_nextword(s, c);
		count++;
	}
	wordarr[count] = 0;
	return (wordarr);
}
