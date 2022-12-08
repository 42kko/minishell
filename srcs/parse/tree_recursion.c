/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_ recursion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:09:16 by kko               #+#    #+#             */
/*   Updated: 2022/12/09 02:15:31 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*redir_null(t_info *info)
{
	t_token	*tmp;

	tmp = new_token(info);
	tmp->type = NO_REDIR;
	return (tmp);
}

static t_token	*cmd_tree(t_token *tok, int i)
{
	t_token	*cmd;
	t_token	*tmp;

	cmd = new_token(tok->info);
	cmd->type = TRDYCMD;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type != TCMD && tmp->type != TNOCMD)
			i = 1;
		if (tmp->type == TCMD || tmp->type == TNOCMD)
			break ;
		tmp = tmp->next;
	}
	if (i == 1)
	{
		tmp->prev->next = 0;
		tmp->prev = 0;
		cmd->left = tok;
	}
	else
		cmd->left = redir_null(tok->info);
	cmd->right = tmp;
	return (cmd);
}

static t_token	*brach_tree(t_token *tok, int i)
{
	t_token	*cmd;
	t_token	*tmp;

	cmd = new_token(tok->info);
	cmd->type = TRDYBRACH;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type != TBRACH)
			i = 1;
		if (tmp->type == TBRACH)
			break ;
		tmp = tmp->next;
	}
	if (i == 1)
	{
		tmp->prev->next = 0;
		tmp->prev = 0;
		cmd->left = tok;
	}
	else
		cmd->left = redir_null(tok->info);
	cmd->right = tmp;
	return (cmd);
}

static t_token	*cmd_brach(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp->type != TCMD && tmp->type != TBRACH && tmp->type != TNOCMD)
		tmp = tmp->next;
	if (tmp->type == TCMD || tmp->type == TNOCMD)
		tmp = cmd_tree(tok, 0);
	else if (tmp->type == TBRACH)
		tmp = brach_tree(tok, 0);
	return (tmp);
}

t_token	*get_tree(t_token *token)
{
	t_token		*tmp;
	t_oper_type	oper1;
	t_oper_type	oper2;
	t_oper_type	oper3;

	if (token == 0)
		return (0);
	zero_parameter(&oper1, &oper2, &oper3);
	tmp = token;
	select_oper(token, &oper1, &oper2, &oper3);
	if (oper1 == 0 && (token->type == TIN || token->type == TOUT || \
	token->type == TDOC || token->type == TADDOUT || token->type == TCMD || \
	token->type == TBRACH || token->type == TNOCMD))
		return (cmd_brach(ft_tokenstart(token)));
	while (tmp)
	{
		if (tmp->type == oper1 || tmp->type == oper2 || tmp->type == oper3)
		{
			tmp->left = get_tree(prev_token(tmp));
			tmp->right = get_tree(next_token(tmp));
			return (tmp);
		}
		tmp = tmp->prev;
	}
	return (token);
}
