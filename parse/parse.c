/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
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
#include <unistd.h>

// check if str is contains syntax
// flag 1 prints the syntax error
// return the invalid syntax symbol
static char	*syntax_cmp(char *line)
{
	int			i;
	int			len;
	static char	*invalid[] = {
		"<<",
		">>",
		"|",
		"<",
		">"
	};

	i = 0;
	while (i < 5)
	{
		len = ft_strlen(invalid[i]);
		if (ft_strncmp(line, invalid[i], len) == 0)
			return (invalid[i]);
		i++;
	}
	return (NULL);
}

static int	print_syntax_error(char *cur, char *prev)
{
	if (cur == NULL || prev == NULL)
		return (0);
	if (*prev == '|' && *cur != '|')
		return (0);
	ft_printf_fd(STDERR_FILENO,
		"idleshell: syntax error near unexpected token `%s'\n", cur);
	return (1);
}

// main syntax check logic
static int	check_syntax(char *line, char **cur, char **prev)
{
	while (*line != 0)
	{
		if (*line == '\'' || *line == '\"')
			line += ft_strlen_t(line, *line);
		if (*line == 0)
			break ;
		*cur = syntax_cmp(line);
		if (print_syntax_error(*cur, *prev))
			return (1);
		if (*line != ' ')
			*prev = *cur;
		if (*cur != NULL)
			line += ft_strlen(*cur);
		else
			line++;
	}
	return (0);
}

// check if str is invalid
// return 1 if syntax error is found
// NOTE: after syntax there must be a non syntax character
int	syntax_error(char *line, t_runtime *runtime)
{
	char	*cur;
	char	*prev;
	int		err;

	cur = NULL;
	prev = NULL;
	err = 0;
	if (!err && !ft_quote_check(line))
		err = 1;
	if (!err && check_syntax(line, &cur, &prev))
		err = 2;
	if (!err && cur != NULL && cur == prev)
		err = 3;
	if (err)
	{
		print_syntax_msg(err, runtime);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
