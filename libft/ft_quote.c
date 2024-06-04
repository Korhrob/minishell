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

// check that str has even amount of quotes
// return 1 if all quotes in str are closed
// return 0 if str has unclosed quotes
int	ft_quote_check(const char *str)
{
	int	flag;

	flag = 0;
	while (*str != 0)
	{
		if (*str == '\'' || *str == '\"')
			flag ^= 1;
		str++;
	}
	return (!(flag & 1));
}

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
