/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:12:24 by kko               #+#    #+#             */
/*   Updated: 2022/12/11 21:38:18 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	zero_parameter(t_oper_type *i, t_oper_type *j, t_oper_type *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

void	zero_parameter1(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
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
