
#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

// if c is any character in set return 1
int	is_charset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

// moves str to first char after << < or >
// then gets length until next syntax symbol
// then copies the chars until that point into a new string
char	*get_filename(char *str)
{
	char	*out;
	int		len;

	while (*str == ' ')
		str++;
	len = 0;
	while (str[len] != 0)
	{
		if (is_charset(str[len], " |<>"))
			break ;
		len++;
	}
	out = (char *) malloc(len + 1);
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, str, len + 1);
	return (out);
}

// check if str is contains syntax
// flag 1 prints the syntax error
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

// check if str is invalid
// return 1 if syntax error is found
int	syntax_error(char *line)
{
	char	*cur;
	char	*prev;

	prev = NULL;
	while (*line != 0)
	{
		cur = syntax_cmp(line);
		if (cur != NULL && prev != NULL)
		{
			ft_printf("syntax error near unexpected token `%s'\n", cur);
			return (1);
		}
		prev = cur;
		if (cur != NULL)
			line += ft_strlen(cur);
		else
			line++;
	}
	if (prev != NULL)
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
