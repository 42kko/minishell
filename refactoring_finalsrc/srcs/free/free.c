/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:23:25 by kko               #+#    #+#             */
/*   Updated: 2023/01/08 13:13:43 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (cmd == 0)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = 0;
		i++;
	}
	free(cmd);
	cmd = 0;
}

int	free_lst(t_token *tok, t_info *info)
{
	t_token	*tmp;

	tmp = tok;
	while (tok)
	{
		tmp = tok;
		free_cmd(tok->cmd);
		free(tok->line);
		tok->line = 0;
		tok = tok->next;
		free(tmp);
	}
	return (err_msg_syntax_int(info));
}

void	free_prev_tok(t_token *tok)
{
	t_token	*tmp;

	if (tok->next == 0)
		return ;
	tok = tok->next;
	while (tok)
	{
		free(tok->line);
		tok->line = 0;
		tmp = tok;
		free(tmp);
		tok = tok->next;
	}
}

void	free_tree(t_token *tok)
{
	if (tok == NULL)
		return ;
	free_tree(tok->left);
	free_tree(tok->right);
	free_cmd(tok->cmd);
	if (tok->type == TIN || tok->type == TADDOUT || \
	tok->type == TDOC || tok->type == TOUT)
	{
		if (tok->fd_in != -1)
			close_util(tok->fd_in, tok);
		if (tok->fd_out != -1)
			close_util(tok->fd_out, tok);
		free_prev_tok(tok);
	}
	if (tok->line != NULL)
	{
		free(tok->line);
		tok->line = 0;
	}
	free(tok);
	tok = 0;
	return ;
}
