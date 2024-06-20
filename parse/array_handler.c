#include "../minishell.h"
#include <stdlib.h>

// sets flag to 1 if string consist only of < or >
static void	set_flag(char *str, int *flag)
{
	if (is_charset(*str, "<>"))
	{
		while (is_charset(*str, "<>"))
			str++;
		if (*str == 0)
			*flag = 1;
	}
}

// swap two strings pointers
static void	ft_swap_str(char **s1, char **s2)
{
	char	*t;

	t = *s1;
	*s1 = *s2;
	*s2 = t;
}

// "cut" of any part of string after <>
static void ft_cut_str(char **str, const char *set)
{
	int	i;

	i = 0;
	while ((*str)[i] != 0)
	{
		if (is_charset((*str)[i], set))
		{
			while ((*str)[i] != 0)
			{
				(*str)[i]  = 0;
				i++;
			}
		}
		else
			i++;
	}
}

static void	clear_array(char **arr)
{
	while (*arr != NULL)
	{
		free(*arr);
		*arr = NULL;
		arr++;
	}
}

// rebind command and its args to the start of arg, free redirections
void	rebind_args(t_process *p)
{
	int		flag;
	int		i;
	char	**cmd;

	flag = 0;
	i = 0;
	cmd = p->args;
	while (*cmd != NULL)
	{
		set_flag(*cmd, &flag);
		if (!is_charset(**cmd, "<>"))
		{
			if (flag == 0)
			{
				ft_swap_str(&p->args[i], &cmd[0]);
				ft_cut_str(&p->args[i], "<>");
				i++;
			}
			flag = 0;
		}
		cmd++;
	}
	clear_array(&p->args[i]);
}
