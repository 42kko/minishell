/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:22:19 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/25 12:26:29 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct termios	old_term;
struct termios	term;

void	handler(int signo) //시그널핸들러
{
	if (signo == SIGINT)
	{
		printf("\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
		return ;
	else if (signo == SIGTERM)
		printf("exit\n");
	return ;
}

void	initial(void) //초기작업.
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTERM, handler);
	tcgetattr(STDIN_FILENO, &term);
	old_term = term;
	term.c_cflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int ac, char **av, char **envp)
{
	initial(); //초기작업. 여기서 환경변수 및 시그널을 컨트롤할듯
	loop(); //readline 을 받아줄곳.
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	printf("done\n");
	return (0);
}
