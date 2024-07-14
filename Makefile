CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g
LDFLAG		=	#-g -fsanitize=address
RL_INC		=	#-I ~/.brew/opt/readline/include/readline
RL_LIB		=	#-L ~/.brew/opt/readline/lib
NAME		=	idleshell #rename to minishell later
SRC			=	main.c history.c signal.c process.c heredoc.c environments.c
PARSE		=	parse/parse.c parse/file_redirection.c parse/array_handler.c
BUILTIN		=	builtins/builtin_pwd.c builtins/builtin_cd.c builtins/builtin_env.c builtins/builtin_unset.c	\
				builtins/builtin_export.c builtins/builtin_echo.c builtins/builtin_utils.c
PIPEX		=	pipex/pipex.c pipex/redirect.c pipex/path.c
EXPANSION	=	expansions/expansions.c expansions/expansion_utils1.c expansions/expansion_utils2.c
OBJ			=	$(SRC:.c=.o) $(PARSE:.c=.o) $(BUILTIN:.c=.o) $(PIPEX:.c=.o) $(EXPANSION:.c=.o)
LIBFT		=	libft
LIBFT_LIB	=	$(LIBFT)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\x1b[0;2m"
	$(MAKE) -C $(LIBFT)
	@echo "\x1b[0;92m"
	$(CC) -o $(NAME) $(OBJ) $(LIBFT_LIB) -lreadline $(RL_INC) $(RL_LIB) $(LDFLAG)
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

re: clean all

.PHONY: all clean fclean re
