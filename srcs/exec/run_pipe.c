/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/12/09 16:16:31 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child(t_token *tok, int i, t_pipe *pip)
{
	int	tmp;

	tok->info->exit_num = 0;
	set_signal(DFL);
	errno = 0;
	tmp = 0;
	while (i > tmp)
	{
		tok = tok->parent;
		if (i == tmp + 1)
			tok = tok->right;
		tmp++;
	}
	io_ctl(pip, i, tok->left);
	if (tok->right->type == TNOCMD)
		exit (0);
	if (identify_built_exec(tok->right) != 1)
	{
		add_path(tok->right);
		execve(tok->right->cmd[0], tok->right->cmd, \
		get_env_arr(tok->info->env_list));
	}
	else
		ft_bulitin(tok->right);
	exit(errno);
}

static void	ft_parent(int i, t_pipe *pip, t_token *tok)
{
	if (pip->cnt > i)
		close_util(pip->p[(i * 2) + 1], tok);
	if (pip->cnt > i + 1)
	{
		if (pipe(pip->p + ((i + 1) * 2)) < 0)
			err_msg("pipe err", tok, 0);
	}
	if (i > 1 && pip->cnt + 1 > i)
		close_util(pip->p[((i - 2) * 2)], tok);
}

static void	waitpid_stat(t_token *tok, int i)
{
	int	stat;

	while (i > 0)
	{
		waitpid(-1, &stat, 0);
		i--;
	}
	if (WIFEXITED(stat))
		tok->info->exit_num = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
		tok->info->exit_num = WTERMSIG(stat);
}

void	run_pipe(t_token *tok)
{
	struct s_pipe	pip;
	int				i;
	pid_t			pid;

	i = 0;
	new_pipe(&pip);
	pip.cnt = cnt_pipe(&tok);
	pip.p = (int *)malloc(sizeof(int) * pip.cnt * 2);
	if (pipe(pip.p) < 0)
		err_msg("pipe_err", tok, 0);
	while (i < pip.cnt + 1)
	{
		pid = fork();
		if (pid == 0)
			ft_child(tok, i, &pip);
		else if (pid > 0)
			ft_parent(i, &pip, tok);
		i++;
	}
	if (pip.p[((i - 1) * 2)] != 0 && pip.p[((i - 1) * 2)] != 1)
		close_util(pip.p[((i - 1) * 2)], tok);
	waitpid_stat(tok, i);
	free(pip.p);
}
