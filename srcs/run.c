/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/12/05 21:43:51 by ko               ###   ########.fr       */
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

void	exec(t_token *tok)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == 0)
	{
		printf("errno:%d\n", errno);
		execve(tok->cmd[0], tok->cmd, 0);
		printf("err\n");
		exit(errno);
	}
	else if (pid > 0)
		waitpid(-1, &stat, 0);
	if (WIFEXITED(stat))
	{
		printf("exit:%d\n",WEXITSTATUS(stat));
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
		if (identify_built_exec(tok) == 1)
		{
			// bulitin();
		}
		if (identify_built_exec(tok) == 0)
		{
			exec(tok);
		}
		run_shell(tok->right);
	}
}

// /bin/ls | /bin/ls | /usr/bin/wc