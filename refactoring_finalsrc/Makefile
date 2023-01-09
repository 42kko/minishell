# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 15:22:25 by seokchoi          #+#    #+#              #
#    Updated: 2023/01/08 14:14:20 by jihonkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = main.c initial.c loop.c
SRCS_BULT=  ft_cd.c ft_echo.c ft_env.c ft_export.c ft_pwd.c ft_unset.c \
			export_util.c ft_exit.c ft_export_util.c
SRCS_ENV= ft_split_for_env.c env.c free.c env_arr.c check_env.c ft_unset_env_list.c
SRCS_ERR= err.c err_msg_syntax_int.c
SRCS_EXE= built_run.c exec.c here_doc.c ioctl.c open_redir.c open_redir_util.c open_redir_wild.c \
			open_util.c path.c pipe_util.c run_pipe.c run.c
SRCS_PAR= check_list.c check_list2.c check_subshell_redir.c check_wave.c \
			cmd.c cut_cmd.c delete_comma_check_env.c ft_strjoin_space.c \
			init_token.c is_type.c key_util.c malloc_utils.c oper_type.c \
			parse_utility.c push_index_about_comma.c redirection.c \
			redirection2.c token_list_len.c token_util.c tree_check.c \
			tree_recursion.c tree_util.c wildcard_dir.c wildcard.c \
			wildcard_arrs.c wildcard_com.c wildcard_utility.c
SRCS_FREE= free.c utility.c
SOURCE	= srcs/
SRC_ENV = srcs/env/
SRC_PAR = srcs/parse/
SRC_BULT= srcs/builtin/
SRC_EXE= srcs/exec/
SRC_ERR= srcs/error/
SRC_FREE= srcs/free/
OBJS	= ${addprefix ${SOURCE},${SRCS:.c=.o}} ${addprefix ${SRC_ENV},${SRCS_ENV:.c=.o}} \
			${addprefix ${SRC_PAR},${SRCS_PAR:.c=.o}} ${addprefix ${SRC_BULT},${SRCS_BULT:.c=.o}} \
			${addprefix ${SRC_EXE},${SRCS_EXE:.c=.o}} ${addprefix ${SRC_ERR},${SRCS_ERR:.c=.o}} \
			${addprefix ${SRC_FREE},${SRCS_FREE:.c=.o}}
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
NAME    = minishell
HEAD	= includes
LIBFT	= libft

all:		${NAME}

.c.o:		${SRCS}
			${CC} $(CFLAGS) -I ${HEAD} -c $^ -o ${^:.c=.o} -I/Users/jihonkim/.brew/opt/readline/include

${NAME}:	${OBJS}
			make -C ${LIBFT}/ 
			$(CC) $(CFLAGS) -I $(HEAD) -o $(NAME) ${OBJS} -L/Users/jihonkim/.brew/opt/readline/lib -lreadline  -L ./libft -lft

clean:
			make clean -C ${LIBFT}/
			rm -f ${OBJS}

fclean:		clean
			make fclean -C ${LIBFT}/
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
