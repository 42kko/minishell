/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:24:01 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 02:11:33 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include "parse.h"
# include "env.h"
# include "builtin.h"
# include "exec.h"
# include "free.h"
# include "libft.h"
# include "err.h"

# define SUCCESS	1
# define FAIL		0

//initial
void	initial(t_info *info, char **envp);
void	set_signal(int num);

//loop
int		run(char *line, t_info *info);
void	loop(t_info *info);

//test
void	printf_line(t_token *lst);
void	printf_type(t_oper_type s);
void	func(char *s);
void	show_list_type_data(t_token *lst);
void	ft_tokeniter(t_token *lst);
void	printf_key(t_keys *keys);
void	printf_env(char **arr);

#endif