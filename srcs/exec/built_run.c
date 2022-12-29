/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:22:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/30 00:26:13 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builitin(t_token *tok)
{
	if (tok->type != TCMD)
		return (-1);
	if (ft_strncmp(tok->cmd[0], "echo", 5) == 0)
		ft_echo(tok->cmd, tok);
	else if (ft_strncmp(tok->cmd[0], "cd", 3) == 0)
		ft_cd(tok);
	else if (ft_strncmp(tok->cmd[0], "pwd", 4) == 0)
	{
		ft_pwd(tok->cmd);
		tok->info->exit_num = 0;
	}
	else if (ft_strncmp(tok->cmd[0], "export", 7) == 0)
		ft_export(tok);
	else if (ft_strncmp(tok->cmd[0], "unset", 5) == 0)
		ft_unset(tok);
	else if (ft_strncmp(tok->cmd[0], "env", 4) == 0)
		ft_env(tok);
	else if (ft_strncmp(tok->cmd[0], "exit", 5) == 0)
		ft_exit(tok, tok->cmd);
	return (0);
}

void	builtin_alone_exec(t_token *tok)
{
	set_signal(DFL);
	if (tok->left->type != NO_REDIR)
		io_ctl_cmd(tok->left);
	if (tok->right->type == TNOCMD)
		return ;
	ft_builitin(tok->right);
	if (tok->fd_in != -1)
		close_util(tok->fd_in, tok);
	if (tok->fd_out != -1)
		close_util(tok->fd_out, tok);
	set_signal(BASH);
}
