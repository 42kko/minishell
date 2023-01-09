/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:20:15 by kko               #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/29 23:29:02 by ko               ###   ########.fr       */
=======
/*   Updated: 2022/12/12 20:08:56 by kko              ###   ########.fr       */
>>>>>>> parent of 6b4336f... 찐막 아니면 죽음
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signo)
{
	int	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
	g_errno = 1;
	(void) signo;
}

static void	handler1(int signo)
{
	int	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	(void) signo;
}

void	initial(t_info *info, char **envp)
{
	// struct termios	term;

	init_env(info, envp);
	set_signal(BASH);
	// tcgetattr(STDIN_FILENO, &term);
	// tcgetattr(STDIN_FILENO, info->old_term);
	// term.c_lflag &= ~(ECHOCTL);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_signal(int num)
{
	if (num == BASH)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == FORK)
	{
		signal(SIGINT, handler1);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == DFL)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == DOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == IGN)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
