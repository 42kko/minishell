/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:24:01 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/07 20:24:19 by seokchoi         ###   ########.fr       */
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
# include "libft.h"
# include "env.h"
# include "parse.h"
# include "builtin.h"
# include <sys/wait.h>

# define SECCESS	1
# define FAIL		0

extern int	g_errno;

void	loop(t_info *info);

// throw_error
void	throw_error(t_error_type type);
void	throw_error_message(char *cmd, char *err, char *message, int exit_errno);

int		ft_bulitin(t_token *tok);
void	built_exec(t_token *tok);
void	builtin_alone_exec(t_token *tok);

#endif