/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/12/07 03:31:18 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	io_ctl(t_pipe *pip, int i, t_token *tok)
{
	if (pip->cnt > i)
	{
		close(pip->p[(i * 2)]);
	}
	if (tok->type != NO_REDIR && tok->fd_in != -1)
	{
		dup2(tok->fd_in, 0);
		close(tok->fd_in);
	}
	else
	{
		if (i > 0) 
		{
			dup2(pip->p[(i - 1) * 2], 0); 
			close(pip->p[(i - 1) * 2]);
		}
	}
	if (tok->type != NO_REDIR && tok->fd_out != -1)
	{
		dup2(tok->fd_out, 1);
		close(tok->fd_out);
	}
	else
	{
		if (i < pip->cnt) 
		{
			dup2(pip->p[(i * 2) + 1], 1);
			close(pip->p[(i * 2) + 1]);
		}
	}
}

void	ft_child(t_token *tok, int i, t_pipe *pip)
{
	int	tmp;

	set_signal(DFL);
	errno = 0;
	tmp = 0;
	while (i > tmp) //다중파이프일때 2, 3번째 명령어들은 현재 노드의 위에있으므로 해당 위치로 이동시켜줌
	{
		tok = tok->parent; //i 만큼 부모노드로 이동한뒤
		if (i == tmp + 1)
			tok = tok->right; //RDYCMD로 이동해줌
		tmp++;
	}
	io_ctl(pip, i, tok->left); //받아온 fd값을 가지고 입,출력을 바꿔줄함수
	if (tok->right->type == TNOCMD)
		exit (0);
	add_path(tok->right, tok->info);
	execve(tok->right->cmd[0], tok->right->cmd, get_env_arr(tok->info->env_list));
	exit(errno); //실행이되지않았다면 exit으로 끝냄.
}

/*
부모프로세서에서는 다음 인덱스에서 자식프로세서가 쓸 파이프를 미리 열어줘야함
e.g
cnt = 2일때 파이프가 2개가 열려야함.
cmd0 - 1 을 이어줄 파이프는 while문 시작전에 열어줌  (1)
그다음 cmd1 - 2 를 연결해줄파이프를 index 0일때 미리 열어줘야함  (2)
그리고 안쓰는 파이프들을 적절히 닫아줌.
*/
void	ft_parent(int i, t_pipe *pip) 
{
	if (pip->cnt > i)
		close(pip->p[(i * 2) + 1]);
	if (pip->cnt > i + 1)
		pipe(pip->p + ((i + 1) * 2));
	if (i > 1 && pip->cnt + 1 > i)
		close(pip->p[((i - 2) * 2)]);
}

void	new_pipe(t_pipe *pip)
{
	pip->cnt = 0;
	pip->p = 0;
}

int	cnt_pipe(t_token **tok)
{
	int	ret;

	ret = 0;
	while ((*tok)->left)
	{
		if ((*tok)->type == TPIPE)
			ret++;
		*tok = (*tok)->left;
	}
	(*tok) = (*tok)->parent;
	return (ret);
}

void	run_pipe(t_token *tok)
{
	struct s_pipe	pip;
	int i = 0;

	new_pipe(&pip); //파이프에서 사용할 구조체
	pip.cnt = cnt_pipe(&tok);
	pip.p = (int *)malloc(sizeof(int) * pip.cnt * 2); //필요한 파이프만큼 오픈
	pipe(pip.p); //첫파이프 오픈
	while (i < pip.cnt + 1) //실행할 횟수는 명령어갯수만큼.
	{
		pid_t pid = fork();
		if (pid == 0)
			ft_child(tok, i, &pip);
		else if (pid > 0)
			ft_parent(i, &pip);
		i++;
	}
	if (pip.p[((i - 1) * 2)] != 0 && pip.p[((i - 1) * 2)] != 1)
		close(pip.p[((i - 1) * 2)]);
	while (i-- > 0) //자식이 열렸던만큼 기다려줌.
		waitpid(-1, 0, 0);
	free(pip.p);
}