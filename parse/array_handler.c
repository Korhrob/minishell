/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

#include <unistd.h> // DEBUG

// sets flag to 1 if string consist only of < or >
// should not include space in initial check(?)
static void	set_flag(char *str, int *flag)
{
	if (is_charset(*str, "<>"))
	{
		while (is_charset(*str, "<> "))
			str++;
		if (*str == 0)
			*flag = 1;
	}
}

// swap two pointers
static void	ft_swap_ptr(void **s1, void **s2)
{
	void	*t;

	t = *s1;
	*s1 = *s2;
	*s2 = t;
}

// "cut" of any part of string after <>
static void	ft_cut_str(char **str, const char *set)
{
	int	i;

	i = 0;
	while ((*str)[i] != 0)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{	
			i += ft_strlen_t((*str + i), (*str)[i]);
			continue ;
		}
		if (is_charset((*str)[i], set))
		{
			while ((*str)[i] != 0)
			{
				(*str)[i] = 0;
				i++;
			}
			continue ;
		}
		i++;
	}
}

// rebind command and its args to the start of arg, free redirections
void	rebind_args(char **args, t_process *p)
{
	int		i;
	int		flag;
	char	*line;

	i = 0;
	flag = 0;
	while (*args != NULL)
	{
		line = *args;
		set_flag(line, &flag);
		if (*line == '\'' || *line == '\"')
			line += ft_strlen_t(line, *line);
		if (!is_charset(*line, "<>"))
		{
			if (flag == 0)
			{
				ft_cut_str(&p->args[i], "<>");
				ft_swap_ptr((void *)&p->args[i], (void *)&args[0]);
				i++;
			}
			flag = 0;
		}
		args++;
	}
	ft_clear_arr(&p->args[i]);
}
