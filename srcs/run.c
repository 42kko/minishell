/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/12/02 21:24:17 by ko               ###   ########.fr       */
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



void	run_shell(t_token *tok)
{
	if (tok == 0)
		return ;
	if (tok->type == TPIPE)
	{
		run_pipe(tok);
		// run(tok->left);
		// run(tok->right);
	}
	// else if (tok->type == TRDYCMD)
	// {
	// 	execve(tok->right->cmd[0], tok->right->cmd, 0);
	// }
	else
	{
		run_shell(tok->left);
		run_shell(tok->right);
	}
}

// /bin/ls | /bin/ls | /usr/bin/wc