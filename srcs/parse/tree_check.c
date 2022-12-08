/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:27:09 by kko               #+#    #+#             */
/*   Updated: 2022/12/09 02:30:24 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	viewtree(t_token *tok)
{
	int	i;

	i = 0;
	if (tok == 0)
		return ;
	viewtree(tok->left);
	if (tok->left)
		tok->left->parent = tok;
	if (tok->right)
		tok->right->parent = tok;
	viewtree(tok->right);
}

void	viewtree2(t_token *tok)
{
	t_token	*tmp;

	if (tok == 0)
		return ;
	if (tok->err_flag_syn == 1)
	{
		tmp = tok;
		while (tmp->parent)
			tmp = tmp->parent;
		tmp->err_flag_syn = 1;
	}
	viewtree2(tok->left);
	viewtree2(tok->right);
}

int	check_tree(t_token *token)
{
	viewtree(token);
	viewtree2(token);
	if (token->err_flag_syn == 1)
	{
		free_tree(token);
		return (1);
	}
	return (0);
}
