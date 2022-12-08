/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 08:19:19 by kko               #+#    #+#             */
/*   Updated: 2022/12/08 16:12:10 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*redir_null(t_info *info)
{
	t_token	*tmp;

	tmp = new_token(info);
	tmp->type = NO_REDIR;
	return (tmp);
}

t_token	*cmd_tree(t_token *tok, int i)
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

t_token	*brach_tree(t_token *tok, int i)
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

t_token	*cmd_brach(t_token *tok)
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

void	zero_parameter(t_oper_type *i, t_oper_type *j, t_oper_type *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
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

void	extra_work_tree(t_token *tok) //괄호처리 작업예정.
{
	t_token	*tmp;

		return ;
	if (tok == 0)
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == TCMD)
			cmd_tree(tok, 0);
		tmp = tmp->next;
	}
	extra_work_tree(tok->left);
	extra_work_tree(tok->right);
}

t_token	*next_token(t_token *token)
{
	if (token->next == 0)
	{
		throw_error_syntax(SYNTAX_ERR_TREE, token);
		return (NULL);
	}
	token = token->next;
	token->prev->next = 0;
	token->prev = 0;
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*prev_token(t_token *token)
{
	if (token->prev == 0)
	{
		throw_error_syntax(SYNTAX_ERR_TREE, token);
		return (NULL);
	}
	token = token->prev;
	token->next->prev = 0;
	token->next = 0;
	return (token);
}

void	select_oper(t_token *tok, t_oper_type *oper1, \
	t_oper_type *oper2, t_oper_type *oper3)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == TDAND || tmp->type == TOR || tmp->type == TSEMI)
		{
			*oper1 = TDAND;
			*oper2 = TOR;
			*oper3 = TSEMI;
			return ;
		}
		tmp = tmp->prev;
	}
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == TPIPE)
		{
			*oper1 = TPIPE;
			return ;
		}
		tmp = tmp->prev;
	}
}
