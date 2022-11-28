/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/11/28 21:25:01 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exec(t_token *tok)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(tok->right->cmd[0], tok->right->cmd, 0);
		perror("err: ");
		exit(1);
	}
	else if (pid > 0)
		wait(0);
}

t_token *run_start(t_token *tok)
{
	while (tok->left)
		tok = tok->left;
	return (tok);
}

// void	run(t_token *tok)
// {
// 	tok = run_start(tok);
// 	while (tok->parent)
// 	{
// 		if (tok->parent->type == TRDYCMD)
// 			run_exec(tok->parent);
// 		// if (tok->parent->type == TPIPE)
// 		// 	run_pipe(tok->parent);
// 		tok = tok->parent;
// 	}
// }

/*
자식은 오직 실행만하고 부모에서 dup2를 할 예정인데 자식과 부모가 동시에 실행되기때문에 안댐.
+ 부모에서 dup2를 해버리면 나중에 표준입력을 찾아올수잇나? -> 못찾음
부모는 다음꺼를 미리열어줘야함.
*/

void	ft_child(t_token *tok, int i, int *p, int cnt)
{
	close(p[(i * 2)]);
	if (tok->left->type != NO_REDIR)
		ft_redir(tok->left);
	else if (i != cnt) //마지막이 아닐때만 파이프에쓰고, 마지막은 fd 값 신경안쓰고(위작업에서 작업했음) 그냥 실행
	{
		dup2(p[(i * 2) + 1], 1);
		close(p[(i * 2) + 1]);
	}
	execve(tok->right->cmd[0], tok->right->cmd, 0);
	exit(1);
}

void	run_pipe(t_token *tok)
{
	int cnt = 0;
	while (tok->left)
	{
		if (tok->type == TPIPE)
			cnt++;
		tok = tok->left;
	}
	tok = tok->parent;
	int i = 0;
	int p[cnt * 2]; // 총 파이프수만큼 정적할당
	pipe(p); // 처음파이프를 열어줌
	while (i < cnt + 1)
	{
		pid_t pid = fork();
		if (pid == 0)
			ft_child(tok, i, p, cnt);
		else if (pid > 0)
		{
			close(p[i * 2 + 1]); //안쓸꺼닫아줌
			pipe(p + (i * 2)); //cnt 와 i*2 를비교해서 더 열어야한다면 열어줌
		}
		i++;
	}

}

void	run(t_token *tok)
{
	if (tok == 0)
		return ;
	if (tok->type == TPIPE) // 전위 (위에서부터)
	{
		printf("tree : %s\n", tok->line);
		run_pipe(tok);
		// run(tok->left);
		// run(tok->right);
	}
	else // 중위 (맨 왼쪽부터)
	{
		run(tok->left);
		printf("tree : %s\n", tok->line);
		run(tok->right);
	}
}