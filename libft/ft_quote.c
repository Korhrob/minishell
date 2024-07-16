/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:05:39 by rkorhone          #+#    #+#             */
/*   Updated: 2024/05/30 16:05:39 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// check that all quotes in string str are closed
// return 1 if all quotes are closed
// return 0 if contains unclosed quotes
int	ft_quote_check(const char *str)
{
	int		flag;
	char	c;

	flag = 0;
	c = 0;
	while (*str != 0)
	{
		if (c == 0 && (*str == '\'' || *str == '\"'))
			c = *str;
		if (*str == c)
		{
			flag ^= 1;
			if (!(flag & 1))
				c = 0;
		}
		str++;
	}
	return (!(flag & 1));
}

// check that all quotes in string array arr are closed
// return 1 if all quotes are closed
// return 0 if contains unclosed quotes
int	ft_quote_check_arr(char **arr)
{
	char	*cur;

	cur = *arr;
	while (cur != 0)
	{
		if (ft_quote_check(cur) == 0)
			return (0);
		arr++;
		cur = *arr;
	}
	return (1);
}
