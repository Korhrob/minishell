/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:33:13 by rkorhone          #+#    #+#             */
/*   Updated: 2024/05/24 21:56:41 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdarg.h>

int			ft_isalpha(unsigned char c);
int			ft_isdigit(unsigned char c);
int			ft_isdigit_str(char *str);
int			ft_isalnum(unsigned char c);
int			ft_isascii(unsigned char c);
int			ft_isprint(unsigned char c);
size_t		ft_strlen(const char *s);
size_t		ft_strlen_t(const char *str, char c);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strncpy(char *dst, const char *src, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);

void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s1, size_t i, size_t len);

char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strjoin_c(const char *s1, const char *s2, char c);
char		*ft_strtrim(const char *s1, const char *set);
char		**ft_split(const char *s, char c);
char		**ft_split_quotes(const char *s, char c, int flag);
char		*ft_itoa(int n);
void		ft_itoa_buf(char *s, int i);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

int			ft_quote_check(const char *str);
int			ft_quote_check_arr(char **arr);
char		*ft_strtrim_quote(const char *str);
char		**ft_strtrim_quote_arr(char **arr, int flag);
void		*ft_free(void *ptr);
void		*ft_free_arr(char **arr);
void		ft_clear_arr(char **arr);
int			ft_array_len(void **array);
char		*ft_array_join(char **array);
int			file_line_count(char *file);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *element);
void		ft_lstadd_back(t_list **lst, t_list *element);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *list, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));
void		*ft_lst_clean(t_list **list, int mode);

# ifndef LOWERCASE
#  define LOWERCASE "0123456789abcdef"
# endif
# ifndef UPPERCASE
#  define UPPERCASE "0123456789ABCDEF"
# endif

// ft_printf

int			ft_print_chr(int fd, unsigned int c);
int			ft_print_str(int fd, const char *str);
int			ft_print_nbr(int fd, int n, char prefix);
int			ft_print_nbr_u(int fd, unsigned int n);
int			ft_print_hex(int fd, unsigned long n, const char *base, char pfx);
int			ft_print_ptr(int fd, void *ptr);
int			ft_printf(const char *s, ...);
int			ft_printf_fd(int fd, const char *s, ...);

// ft_printf bonus

int			ft_add_or_fail(int *a, int b);
int			ft_print_nbr_bonus(int fd, const char *s, va_list args, char pfx);
int			ft_print_str_bonus(int fd, const char *s, va_list args);

// get_next_line

struct s_read_buffer
{
	int		index;
	int		start;
	int		bytes;
	char	*str;
};

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*init_str(char **src, int add_len);
char		*copy_str(char *dest, struct s_read_buffer *buffer, int add_len);

void		init_buffer(int fd, struct s_read_buffer *buffer);
void		*free_buffer(struct s_read_buffer *buffer, char **output);
void		*malloc_fail(char *str, struct s_read_buffer *buffer);
char		*get_next_line(int fd);

#endif