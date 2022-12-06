/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/12/06 21:21:31 by kko              ###   ########.fr       */
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
		errno = 0;
		if (tok->left->type != NO_REDIR)
			io_ctl_cmd(tok->left);
		execve(tok->right->cmd[0], tok->right->cmd, 0);
		exit(errno);
	}
	else if (pid > 0)
		waitpid(-1, &stat, 0);
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
	add_path(tok->right, tok->info);
	if (identify_built_exec(tok->right) == 1) //빌트인
	{
		// bulitin();
	}
	else if (identify_built_exec(tok->right) == 0) //exec
	{
		exec(tok);
	}
}

void	run_shell(t_token *tok)
{
	if (tok == 0)
		return ;
	if (tok->type == TPIPE)
	{
		run_pipe(tok);
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
