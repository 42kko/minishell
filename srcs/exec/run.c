/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:31:54 by kko               #+#    #+#             */
/*   Updated: 2022/12/10 06:37:25 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_exec(t_token *tok)
{
	if (tok->err_flag_redir == -1)
	{
		tok->info->exit_num = 1;
		return ;
	}
	if (identify_built_exec(tok->right) == 1)
	{
		builtin_alone_exec(tok);
	}
	else if (identify_built_exec(tok->right) == 0)
	{
		set_signal(IGN);
		exec(tok);
		set_signal(BASH);
	}
}

static void	run_subshell(t_token *tok)
{
	pid_t	pid;
	int		stat;

	if (tok->err_flag_redir == -1)
		return ;
	pid = fork_util(tok);
	if (pid == 0)
	{
		set_signal(DFL);
		errno = 0;
		if (tok->left->type != NO_REDIR)
			io_ctl_cmd(tok->left);
		exit(run(tok->right->line, tok->info));
	}
	else if (pid > 0)
		wait(&stat);
	if (WIFEXITED(stat))
		tok->info->exit_num = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
		tok->info->exit_num = WTERMSIG(stat);
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
		if (tok->type == TRDYCMD)
		{
			run_exec(tok);
		}
		if (tok->type == TRDYBRACH)
			run_subshell(tok);
		if ((tok->type == TDAND && tok->info->exit_num == 0) || \
		(tok->type == TOR && tok->info->exit_num != 0))
			run_shell(tok->right);
	}
}
