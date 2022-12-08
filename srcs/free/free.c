/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:23:25 by kko               #+#    #+#             */
/*   Updated: 2022/12/08 23:24:06 by kko              ###   ########.fr       */
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

int	free_lst(t_token *tok)
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
	printf("syntax error\n");
	return (1);
}

void	free_tree(t_token *tok)
{
	if (tok == NULL)
		return ;
	free_tree(tok->left);
	free_tree(tok->right);
	free_cmd(tok->cmd);
	if (tok->line != NULL)
	{
		free(tok->line);
		tok->line = 0;
	}
	free(tok);
	tok = 0;
	return ;
}
