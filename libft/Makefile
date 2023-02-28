# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 04:30:10 by sciftci           #+#    #+#              #
#    Updated: 2023/02/28 04:30:11 by sciftci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CFLAGS	=	-Wall -Wextra -Werror
HEAD	=	libft.h
AR		=	ar -rcs
RM		=	rm -rf

SRC	=	ft_atol.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_itoa.c\
		ft_putstr_fd.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strcmp.c\
		ft_strcpy.c\
		ft_strjoin.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_substr.c\
		ft_strdup.c\
		
OBJ		=	$(SRC:.c=.o)

$(NAME): ${OBJ}
			${AR} ${NAME} ${OBJ}
			
all:	${NAME}

clean:	 
		${RM} ${OBJ}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re