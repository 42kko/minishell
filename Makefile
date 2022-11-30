# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 15:22:25 by seokchoi          #+#    #+#              #
#    Updated: 2022/11/29 20:48:18 by seokchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = main.c throw_error.c utility.c loop.c token_list.c test.c
SRCS_ENV= ft_split_for_env.c env.c free.c
SRCS_PAR= cmd.c init_token.c is_type.c oper_type.c parse_utility.c \
			redirection.c ft_strjoin_space.c tree.c check_env.c \
			push_index_about_comma.c delete_comma_check_env.c \
			token_list_len.c malloc_utils.c
SOURCE	= srcs/
SRC_ENV = srcs/env/
SRC_PAR = srcs/parse/
OBJS	= ${addprefix ${SOURCE},${SRCS:.c=.o}} ${addprefix ${SRC_ENV},${SRCS_ENV:.c=.o}} ${addprefix ${SRC_PAR},${SRCS_PAR:.c=.o}}
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -fsanitize=address
# CFLAGS	= -Wall -Werror -Wextra
NAME    = minishell
HEAD	= includes
LIBFT	= libft

all:		${NAME}

.c.o:		${SRCS}
			${CC} -I ${HEAD} -c $^ -o ${^:.c=.o} -L ./libft -lft -L/opt/homebrew/opt/readline/lib  -I/opt/homebrew/opt/readline/include  -lreadline
#			${CC} -I ${HEAD} -c $^ -o ${^:.c=.o} -L ./libft -lft -L/goinfre/seokchoi/.brew/opt/readline/lib  -I/goinfre/seokchoi/.brew/opt/readline/include  -lreadline

${NAME}:	${OBJS}
			make -C ${LIBFT}/ 
			$(CC) $(CFLAGS) -I $(HEAD) -o $(NAME) ${OBJS} -L ./libft -lft -L/opt/homebrew/opt/readline/lib  -I/opt/homebrew/opt/readline/include  -lreadline
#			$(CC) $(CFLAGS) -I $(HEAD) -o $(NAME) ${OBJS} -L ./libft -lft -L/goinfre/seokchoi/.brew/opt/readline/lib  -I/goinfre/seokchoi/.brew/opt/readline/include  -lreadline

clean:
			make clean -C ${LIBFT}/
			rm -f ${OBJS}

fclean:		clean
			make fclean -C ${LIBFT}/
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re