CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
SRC		=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strlen.c ft_strcmp.c ft_strdup.c \
			ft_strlcpy.c ft_strlcat.c ft_strrchr.c ft_strncmp.c ft_strnstr.c \
			ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_calloc.c ft_bzero.c \
			ft_atoi.c ft_itoa.c ft_substr.c ft_strjoin.c ft_strtrim.c \
			ft_split.c ft_split_quotes.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_printf.c ft_printf_util.c ft_printf_bonus.c \
			ft_print_chr.c ft_print_hex.c ft_print_nbr.c ft_print_ptr.c ft_print_str.c \
			get_next_line.c get_next_line_utils.c ft_quote.c \
			ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
			ft_free.c ft_free_arr.c ft_arr_len.c ft_arr_join.c file_line_count.c ft_strtrim_quote.c
OBJ		=	$(SRC:.c=.o)
NAME	=	libft.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY : all bonus clean fclean re
