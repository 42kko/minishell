/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:22:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 22:22:23 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builitin(t_token *tok)
{
	if (tok->type != TCMD)
		return (-1);
	if (ft_strncmp(tok->cmd[0], "echo", 5) == 0)
		ft_echo(tok->cmd);
	else if (ft_strncmp(tok->cmd[0], "cd", 3) == 0)
		ft_cd(tok);
	else if (ft_strncmp(tok->cmd[0], "pwd", 4) == 0)
		ft_pwd(tok->cmd);
	else if (ft_strncmp(tok->cmd[0], "export", 7) == 0)
		ft_export(tok);
	else if (ft_strncmp(tok->cmd[0], "unset", 5) == 0)
		ft_unset(tok);
	else if (ft_strncmp(tok->cmd[0], "env", 4) == 0)
		ft_env(tok);
	else if (ft_strncmp(tok->cmd[0], "exit", 5) == 0)
	{
		// free_env_list(tok->info->env_list);
		// free_cmd(tok->info->path);
		// free(tok->info);
		exit(0);
	}
	return (0);
}

void	builtin_alone_exec(t_token *tok)
{
	pid_t	pid;
	int		stat;

	set_signal(DFL);
	tok->info->exit_num = 0;
	if (tok->left->type != NO_REDIR)
		io_ctl_cmd(tok->left);
	if (tok->right->type == TNOCMD)
		return ;
	ft_builitin(tok->right);
}
