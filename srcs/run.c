/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/12/07 14:34:12 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_error_syntax(t_error_type type, t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	if (tmp == 0)
		return ;
	if (type == SYNTAX_ERR)
	{
		while (tmp->prev)
			tmp = tmp->prev;
		tmp->err_flag_syn = 1;
	}
	else
		tmp->err_flag_syn = 1;
}

void	io_ctl_cmd(t_token *tok)
{
	if (tok->fd_in != -1)
	{
		dup2(tok->fd_in, 0);
		close_util(tok->fd_in, tok);
	}
	if (tok->fd_out != -1)
	{
		dup2(tok->fd_out, 1);
		close_util(tok->fd_out, tok);
	}
}

void	exec(t_token *tok)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == 0)
	{
		set_signal(DFL);
		errno = 0;
		if (tok->left->type != NO_REDIR)
			io_ctl_cmd(tok->left);
		if (tok->right->type == TNOCMD)
			exit (0);
		add_path(tok->right);
		execve(tok->right->cmd[0], tok->right->cmd, get_env_arr(tok->info->env_list));
		exit(errno);
	}
	else if (pid > 0)
		wait(&stat);
	if (WIFEXITED(stat))
	{
		tok->info->exit_num = WEXITSTATUS(stat);
	}
	else if (WIFSIGNALED(stat))
	{
		tok->info->exit_num = WTERMSIG(stat);
	}
}

void	run_exec(t_token *tok)
{
	if (identify_built_exec(tok->right) == 1) //빌트인
	{
		// ft_bulitin(tok);
	}
	else if (identify_built_exec(tok->right) == 0) //exec
	{
		if (tok->errn != -1)
		{
			set_signal(IGN);
			exec(tok);
			set_signal(BASH);
		}
		else
			tok->info->exit_num = 1;
	}
}

void	run_subshell(t_token *tok)
{
	int	i;

	i = 0;
}

void	run_shell(t_token *tok)
{
	if (tok == 0)
		return ;
	if (tok->type == TPIPE)
	{
		set_signal(FORK);
		run_pipe(tok);
		set_signal(BASH);
	}
	else
	{
		run_shell(tok->left);
		// if (tok->type == TAND && tok->info->exit_num != 0)
		// 	tok->right = 0;
		// else if (tok->type == TOR && tok->info->exit_num == 0)
		// 	tok->right = 0;
		if (tok->type == TRDYCMD)
		{
			run_exec(tok);
		}
		if (tok->type == TBRACH)
			run_subshell(tok);
		if ((tok->type == TDAND && tok->info->exit_num == 0) || \
		(tok->type == TOR && tok->info->exit_num != 0))
			run_shell(tok->right);
	}
}
