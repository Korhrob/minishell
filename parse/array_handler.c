#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>

#include <unistd.h> // DEBUG

// sets flag to 1 if string consist only of < or >
static void	set_flag(char *str, int *flag)
{
	if (is_charset(*str, "<>")) // should this include space?
	{
		while (is_charset(*str, "<> ")) // 
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
static void ft_cut_str(char **str, const char *set)
{
	int	i;

	i = 0;
	while ((*str)[i] != 0)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"') // new addition
			i += ft_strlen_t((*str), (*str)[i]);
		else if (is_charset((*str)[i], set)) // 
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
		ft_printf_fd(STDERR_FILENO, "clear_array [%s]\n", *arr);
		free(*arr);
		*arr = NULL;
		arr++;
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
		//if (*line == '\'' || *line == '\"') // new addition
		//	line += ft_strlen_t(line, *line);
		if (!is_charset(*line, "<>")) // 
		{
			if (flag == 0)
			{
				ft_swap_ptr((void *)&p->args[i], (void *)&args[0]);
				ft_cut_str(&p->args[i], "<>");
				i++;
			}
			flag = 0;
		}
		args++;
	}
	clear_array(&p->args[i]);
}
