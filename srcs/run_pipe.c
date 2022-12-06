/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/12/03 01:31:35 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_util(t_oper_type type, char *line)
{
	int	fd;

	fd = 0;
	while (*line != ' ')
		line++;
	if (type == TOUT)
		fd = open(line, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (type == TADDOUT)
		fd = open(line, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (type == TIN) 
		fd = open(line, O_RDONLY);
	else if (type == TDOC) //히어독모드 추가예정
		fd = 0;
	return (fd);
}

void	ft_redir(t_token *lst, t_pipe *pip)
{
	while (lst)
	{
		if (lst->type == TOUT)
			pip->fd_out = open_util(TOUT, lst->line + 1);
		else if (lst->type == TADDOUT)
			pip->fd_out = open_util(TADDOUT, lst->line + 2);
		else if (lst->type == TIN)
			pip->fd_in = open_util(TIN, lst->line + 1);
		else if (lst->type == TDOC)
			pip->fd_in = open_util(TDOC, lst->line + 2); //아직 here_doc 구현안함
		lst = lst->next;
	}
}

void	io_ctl(t_pipe *pip, int i)
{
	if (pip->cnt > i)
	{
		close(pip->p[(i * 2)]);
	}
	if (pip->fd_in != 0)
	{
		dup2(pip->fd_in, 0);
		close(pip->fd_in);
	}
	else
	{
		if (i > 0) 
		{
			dup2(pip->p[(i - 1) * 2], 0); 
			close(pip->p[(i - 1) * 2]);
		}
	}
	if (pip->fd_out != 0)
	{
		dup2(pip->fd_out, 1);
		close(pip->fd_out);
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

	tmp = 0;
	while (i > tmp) //다중파이프일때 2, 3번째 명령어들은 현재 노드의 위에있으므로 해당 위치로 이동시켜줌
	{
		tok = tok->parent; //i 만큼 부모노드로 이동한뒤 
		if (i == tmp + 1)
			tok = tok->right; //RDYCMD로 이동해줌
		tmp++;
	}
	if (tok->left->type != NO_REDIR) //리다이렉션이 있을경우 fd값을 받아와줌
		ft_redir(tok->left, pip); 
	io_ctl(pip, i); //받아온 fd값을 가지고 입,출력을 바꿔줄함수
	
	execve(tok->right->cmd[0], tok->right->cmd, 0); 
	exit(1); //실행이되지않았다면 exit으로 끝냄.
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
	pip->fd_in = 0;
	pip->fd_out = 0;
}

void	run_pipe(t_token *tok)
{
	struct s_pipe	pip;
	int i = 0;

	new_pipe(&pip); //파이프에서 사용할 구조체
	while (tok->left) //트리구조의 맨아래(첫번째 실행해야할것)로 내려감.(left로 쭉가면 리다이렉션 노드로 도착함.)
	{
		if (tok->type == TPIPE)
			pip.cnt++;
		tok = tok->left;
	}
	tok = tok->parent; //left로 쭉 타고와서 현재는 tok의 위치가 리다이렉션부분임, 한칸올려 RDYCMD로 가서 시작을해줘야함
	pip.p = (int *)malloc(sizeof(int) * pip.cnt * 2); //필요한 파이프만큼 오픈
	pipe(pip.p); //첫파이프 오픈
	while (i < pip.cnt + 1) //실행할 횟수는 명령어갯수만큼.
	{
		pip.fd_out = 0; //초기값으로 설정해줌
		pip.fd_in = 0;
		pid_t pid = fork();
		if (pid == 0)
			ft_child(tok, i, &pip);
		else if (pid > 0)
			ft_parent(i, &pip);
		i++;
	}
	close(pip.p[((i - 1) * 2)]);
	while (i > 0) //자식이 열렸던만큼 기다려줌.
	{
		waitpid(-1, 0, 0);
		i--;
	}
}