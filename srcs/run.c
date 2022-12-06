/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/12/07 03:31:58 by kko              ###   ########.fr       */
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
		close(tok->fd_in);
	}
	if (tok->fd_out != -1)
	{
		dup2(tok->fd_out, 1);
		close(tok->fd_out);
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
		add_path(tok->right, tok->info);
		execve(tok->right->cmd[0], tok->right->cmd, get_env_arr(tok->info->env_list));
		exit(errno);
	}
	else if (pid > 0)
		wait(&stat);
	if (WIFEXITED(stat))
	{
		tok->exit_num = WEXITSTATUS(stat);
	}
	else if (WIFSIGNALED(stat))
	{
		tok->exit_num = WTERMSIG(stat);
		
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
		set_signal(IGN);
		exec(tok);
		set_signal(BASH);
	}
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
		if (tok->type == TAND && tok->left->exit_num != 0)
			tok->right = 0;
		else if (tok->type == TOR && tok->left->exit_num == 0)
			tok->right = 0;
		else if (tok->type == TRDYCMD)
			run_exec(tok);
		run_shell(tok->right);
	}
}
