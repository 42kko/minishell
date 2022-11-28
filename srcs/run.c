/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:58:51 by kko               #+#    #+#             */
/*   Updated: 2022/11/28 18:39:09 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	run_pipe(t_token *tok)
// {
	
// }

void	run_exec(t_token *tok)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(tok->right->cmd[0], tok->right->cmd, 0);
		perror("err: ");
		exit(1);
	}
	else if (pid > 0)
		wait(0);
}

t_token *run_start(t_token *tok)
{
	while (tok->left)
		tok = tok->left;
	return (tok);
}

// void	run(t_token *tok)
// {
// 	tok = run_start(tok);
// 	while (tok->parent)
// 	{
// 		if (tok->parent->type == TRDYCMD)
// 			run_exec(tok->parent);
// 		// if (tok->parent->type == TPIPE)
// 		// 	run_pipe(tok->parent);
// 		tok = tok->parent;
// 	}
// }

void	run(t_token *tok)
{
	if (tok == 0)
		return ;
	if (tok->type == TPIPE) // 전위 (위에서부터)
	{
		printf("tree : %s\n", tok->line);
		run(tok->left);
		run(tok->right);
	}
	else // 중위 (맨 왼쪽부터)
	{
		run(tok->left);
		printf("tree : %s\n", tok->line);
		run(tok->right);
	}
	
}