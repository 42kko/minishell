/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/11/30 17:33:30 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipe
{
	int	cnt;
	int	*p;
	int	fd_out;
	int	fd_in;
}	t_pipe;

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
			pip->fd_in = open_util(TDOC, lst->line + 2);
		lst = lst->next;
	}
}

void	io_ctl(t_pipe *pip, int i)
{
	close(pip->p[(i * 2)]);
	if (pip->fd_in != 0)
		dup2(pip->fd_in, 0);
	else
	{
		if (i > 0)
			dup2(pip->p[(i - 1) * 2], 0);
	}
	if (pip->fd_out != 0)
		dup2(pip->fd_out, 1);
	else
	{
		if (i < pip->cnt)
			dup2(pip->p[(i * 2) + 1], 1);
	}
}

void	ft_child(t_token *tok, int i, t_pipe *pip)
{
	int	tmp;

	tmp = 0;
	while (i > tmp)
	{
		tok = tok->parent;
		if (i == tmp + 1)
			tok = tok->left;
		tmp++;
	}
	if (tok->left->type != NO_REDIR)
		ft_redir(tok->left, pip);
	io_ctl(pip, i);
	execve(tok->right->cmd[0], tok->right->cmd, 0);
	exit(1);
}

void	ft_parent(int i, t_pipe *pip)
{
	if (pip->cnt > i)
		close(pip->p[(i * 2) + 1]);
	if (pip->cnt > i + 1)
		pipe(pip->p + (i * 2));
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

	new_pipe(&pip);
	while (tok->left)
	{
		if (tok->type == TPIPE)
			pip.cnt++;
		tok = tok->left;
	}
	tok = tok->parent;
	pip.p = (int *)malloc(sizeof(int) * pip.cnt * 2);
	pipe(pip.p); // 처음파이프를 열어줌
	while (i < pip.cnt + 1)
	{
		pid_t pid = fork();
		if (pid == 0)
			ft_child(tok, i, &pip);
		else if (pid > 0)
			ft_parent(i, &pip);
		i++;
	}
	close(pip.p[((i - 1) * 2)]);
	while (i > 0)
	{
		waitpid(-1, 0, 0);
		i--;
	}
}

void	run(t_token *tok)
{
	if (tok == 0)
		return ;
	run(tok->left);
	printf("tree : %s\n", tok->line);
	run(tok->right);
}