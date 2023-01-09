/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:22:40 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/03 16:34:51 by jihonkim         ###   ########.fr       */
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
	set_signal(BASH);
}
