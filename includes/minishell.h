/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:24:01 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/29 23:28:17 by ko               ###   ########.fr       */
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

# include <sys/wait.h>


# define SUCCESS	1
# define FAIL		0

extern int	g_errno;

//initial
void	initial(t_info *info, char **envp);
void	set_signal(int num);

//loop
int		run(char *line, t_info *info);
void	loop(t_info *info);

#endif