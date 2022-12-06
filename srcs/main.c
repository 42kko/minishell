/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:22:19 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/06 20:24:27 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_errno; // 여기에 g_errno를 선언하고 minishell.h 에서 extern 을 작성해서 minishell.h를 include하는 모든 파일에서 g.errno를 사용할 수 있게 된다.

void	handler(int signo) //시그널핸들러
{
	if (signo == SIGINT) // cntl + c
	{
		printf("\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1); // 1인 이유는? 
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		printf("ctrl+/");
		return ;
	}
	else if (signo == SIGTERM)
	{
		printf("sig ctrl+d");
		printf("exit\n");
	}
	return ;
}

void	initial(t_info *info) //초기작업.
{
	struct termios	term;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTERM, handler);
	tcgetattr(STDIN_FILENO, &term); // 터미널의 속성을 term에 저장
	tcgetattr(STDIN_FILENO, info->old_term); // 터미널의 속성을 term에 저장
	// term.c_cflag &= ~(ICANON | ECHO);
	// term.c_lflag &= ~(ECHOCTL);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // 변경된 내용을 터미널에 적용
}

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		throw_error(MALLOC_ERR);
	initial(info); //초기작업. 여기서 환경변수 및 시그널을 컨트롤할듯
	loop(envp, info); //readline 을 받아줄곳.
	tcsetattr(STDIN_FILENO, TCSANOW, info->old_term); // 이거해주는 이유는
	printf("done\n");
	return (0);
}
