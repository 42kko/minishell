/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:20:38 by kko               #+#    #+#             */
/*   Updated: 2023/01/03 16:34:58 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_out(t_token *tok, t_token *tmp)
{
	if (tmp->type == TOUT)
	{
		tok->fd_out = open(find_redir(tmp->line + 1), \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (tok->fd_out < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 1));
			tok->fd_out = -1;
			tok->parent->err_flag_redir = -1;
		}
	}
	else if (tmp->type == TADDOUT)
	{
		tok->fd_out = open(find_redir(tmp->line + 2), \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (tok->fd_out < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 2));
			tok->fd_out = -1;
			tok->parent->err_flag_redir = -1;
		}
	}
}

static void	open_in(t_token *tok, t_token *tmp)
{
	if (tmp->type == TIN)
	{
		tok->fd_in = open(find_redir(tmp->line + 1), O_RDONLY);
		if (tok->fd_in < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 1));
			tok->fd_in = -1;
			tok->parent->err_flag_redir = -1;
		}
	}
	else if (tmp->type == TDOC)
	{
		set_signal(FORK);
		signal(SIGQUIT, SIG_IGN);
		tok->fd_in = here_doc(find_redir(tmp->line + 2), tok);
		set_signal(BASH);
	}
}

static void	check_open(t_token *tok, t_token *tmp)
{
	if (tmp->type == TOUT || tmp->type == TADDOUT)
	{
		if (tok->fd_out != -1)
			close_util(tok->fd_out, tok);
		open_out(tok, tmp);
	}
	else if (tmp->type == TIN || tmp->type == TDOC)
	{
		if (tok->fd_in != -1)
			close_util(tok->fd_in, tok);
		open_in(tok, tmp);
	}
}

static void	start_open(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tok->parent->err_flag_redir == -1)
			break ;
		if (tmp->err_flag_redir == 2)
		{
			tok->parent->err_flag_redir = -1;
			break ;
		}
		check_open(tok, tmp);
		tmp = tmp->next;
	}
}

void	open_redir(t_token *tok)
{
	if (tok == 0)
		return ;
	open_redir(tok->left);
	open_redir(tok->right);
	if ((tok->type == TOUT || tok->type == TADDOUT || \
	tok->type == TIN || tok->type == TDOC) && g_errno != -2)
	{
		if (tok->type != TDOC)
			expansion_wild_redir(tok, tok);
		start_open(tok);
	}
}
