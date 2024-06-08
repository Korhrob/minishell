CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
LDFLAG		=	# -g -fsanitize=address
RL			=	-lreadline
RL_PATH		=	# -L ~/.brew/opt/readline/lib # brew readline
NAME		=	idleshell #rename to minishell later
SRC			=	main.c history.c signal.c
OBJ			=	$(SRC:.c=.o)
LIBFT		=	libft
LIBFT_LIB	=	$(LIBFT)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\x1b[0;2m"
	$(MAKE) -C $(LIBFT)
	@echo "\x1b[0;92m"
	$(CC) -o $(NAME) $(OBJ) $(LIBFT_LIB) $(LDFLAG) $(RL) $(RL_PATH)
	@echo $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean
	rm -f .history

re: clean all

.PHONY: all clean fclean re