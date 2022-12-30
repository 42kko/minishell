# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kko <kko@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 18:10:22 by seokchoi          #+#    #+#              #
#    Updated: 2022/12/30 09:54:25 by kko              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c \
			ft_toupper.c ft_calloc.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c\
			ft_itoa.c ft_strmapi.c ft_striteri.c\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 
			
SRCS_BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c 
OBJS	= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}
CC		= cc
#CC		= clang-12
CFLAGS	= -Wall -Werror -Wextra
NAME    = libft.a

ifdef WITH_B
	OBJECTS = $(OBJS) $(OBJS_BONUS)
else
	OBJECTS = $(OBJS)
endif

all :		${NAME}

.c.o:		${SRCS} $(SRCS_BONUS)
			${CC} ${CFLAGS} -c $^

${NAME}:	${OBJECTS}
			ar -rcs $@ ${OBJECTS}

bonus:
			@make WITH_B=1 all

clean:
			rm -f ${OBJS} ${OBJS_BONUS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus