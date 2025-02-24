CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g
LDFLAG		=	#-g -fsanitize=address
NAME		=	minishell
SRC			=	main.c history.c process.c heredoc.c environments.c error.c runtime.c
SIGNAL		=	signal/signal.c signal/signal_handlers.c
PARSE		=	parse/parse.c parse/file_redirection.c parse/array_handler.c parse/parse_utils.c
BUILTIN		=	builtins/builtin_pwd.c builtins/builtin_cd.c builtins/builtin_env.c builtins/builtin_unset.c	\
				builtins/builtin_export.c builtins/builtin_echo.c builtins/builtin_utils.c builtins/builtin.c
PIPEX		=	pipex/pipex.c pipex/redirect.c pipex/path.c pipex/pipex_utils.c
EXPANSION	=	expansions/expansions.c expansions/expansion_utils1.c expansions/expansion_utils2.c
OBJ			=	$(SRC:.c=.o) $(PARSE:.c=.o) $(SIGNAL:.c=.o) $(BUILTIN:.c=.o) $(PIPEX:.c=.o) $(EXPANSION:.c=.o)
LIBFT		=	libft
LIBFT_LIB	=	$(LIBFT)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	rm -rf .tmp
	mkdir .tmp
	$(MAKE) -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT_LIB) -lreadline $(LDFLAG)
	@echo $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean
	rm -f .tmp/*

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean
	rm -rf .tmp

re: clean all

.PHONY: all clean fclean re
