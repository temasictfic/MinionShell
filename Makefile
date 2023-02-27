NAME		=	minishell

HEADER 		= 	minishell.h

LIBFT		=	libft/libft.a

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g -I $(HEADER)


READLINE 	=	-lreadline \
				-L/goinfre/sciftci/homebrew/opt/readline/lib \
				-I/goinfre/sciftci/homebrew/opt/readline/include

SRCS		=	minishell.c\
				0_builtins/env/env_expand.c \
				0_builtins/env/env_get_set.c  \
				0_builtins/env/env.c  \
				0_builtins/cd.c \
				0_builtins/echo.c \
				0_builtins/exit.c \
				0_builtins/export.c \
				0_builtins/pwd.c \
				0_builtins/set.c \
				0_builtins/unset.c  \
				1_exec_builtins/exec_builtin.c \
				2_parse/create_tokens.c \
				2_parse/exec_token.c \
				2_parse/tokenize.c \
				3_pipes/or_and.c \
				3_pipes/pipe_split.c \
				3_pipes/pipe.c \
				4_redirects/heredocs.c \
				4_redirects/redirect_file_functions.c \
				4_redirects/redirect.c \
				5_wildcard/wildcard.c \
				6_utils/error.c \
				6_utils/free.c \
				6_utils/is_env_char.c \
				6_utils/is_only_charset.c \
				6_utils/is_operator.c \
				6_utils/is_quote.c \
				6_utils/is_redir.c \
				6_utils/is_space.c 


OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(LIBFT) $(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(LIBFT) $(OBJS) $(READLINE) -o $(NAME)

$(LIBFT)	:
				make -C ./libft

clean		:
				make clean -C ./libft
				rm -rf $(OBJS)
				

fclean		:	clean
				make fclean -C ./libft
				rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
