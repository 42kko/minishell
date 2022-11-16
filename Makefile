# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 15:22:25 by seokchoi          #+#    #+#              #
#    Updated: 2022/11/16 21:33:39 by seokchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = main.c throw_error.c utility.c loop.c token_list.c
SRCS_ENV= ft_split_for_env.c env.c free.c
SRCS_PAR= 
SOURCE	= srcs/
SRC_ENV = srcs/env/
SRC_PAR = srcs/parse/
OBJS	= ${addprefix ${SOURCE},${SRCS:.c=.o}} ${addprefix ${SRC_ENV},${SRCS_ENV:.c=.o}} ${addprefix ${SRC_PAR},${SRCS_PAR:.c=.o}}
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
NAME    = minishell
HEAD	= includes
LIBFT	= libft

all:		${NAME}

.c.o:		${SRCS}
			${CC} -I ${HEAD} -c $^ -o ${^:.c=.o}

${NAME}:	${OBJS}
			make -C ${LIBFT}/ 
			$(CC) $(CFLAGS) -I $(HEAD) -o $(NAME) ${OBJS} -L ./libft -lft

clean:
			make clean -C ${LIBFT}/
			rm -f ${OBJS}

fclean:		clean
			make fclean -C ${LIBFT}/
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re