/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioctl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:38:32 by kko               #+#    #+#             */
/*   Updated: 2023/01/08 11:51:43 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	io_ctl_cmd(t_token *tok)
{
	if (tok->fd_in != -1)
		dup2(tok->fd_in, 0);
	if (tok->fd_out != -1)
		dup2(tok->fd_out, 1);
}

static void	stdin_ctl(t_pipe *pip, int i, t_token *tok)
{
	if (tok->type != NO_REDIR && tok->fd_in != -1)
	{
		dup2(tok->fd_in, 0);
		close_util(tok->fd_in, tok);
	}
	else
	{
		if (i > 0)
		{
			dup2(pip->p[(i - 1) * 2], 0);
			close_util(pip->p[(i - 1) * 2], tok);
		}
	}
}

static void	stdout_ctl(t_pipe *pip, int i, t_token *tok)
{
	if (tok->type != NO_REDIR && tok->fd_out != -1)
	{
		dup2(tok->fd_out, 1);
		close_util(tok->fd_out, tok);
	}
	else
	{
		if (i < pip->cnt)
		{
			dup2(pip->p[(i * 2) + 1], 1);
			close_util(pip->p[(i * 2) + 1], tok);
		}
	}
}

void	io_ctl(t_pipe *pip, int i, t_token *tok)
{
	if (pip->cnt > i)
		close_util(pip->p[(i * 2)], tok);
	stdin_ctl(pip, i, tok);
	stdout_ctl(pip, i, tok);
}
