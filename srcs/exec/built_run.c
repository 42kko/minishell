/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:22:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 02:43:22 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bulitin(t_token *tok)
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
		exit(0);
	return (0);
}

void	built_exec(t_token *tok)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == 0)
	{
		set_signal(DFL);
		if (tok->left->type != NO_REDIR)
			io_ctl_cmd(tok->left);
		if (tok->right->type == TNOCMD)
			exit (0);
		ft_bulitin(tok->right);
		exit(errno);
	}
	else if (pid > 0)
		wait(&stat);
	if (WIFEXITED(stat))
	{
		tok->info->exit_num = WEXITSTATUS(stat);
	}
	else if (WIFSIGNALED(stat))
	{
		tok->info->exit_num = WTERMSIG(stat);
	}
}

void	builtin_alone_exec(t_token *tok)
{
	pid_t	pid;
	int		stat;

	set_signal(DFL);
	if (tok->left->type != NO_REDIR)
		io_ctl_cmd(tok->left);
	if (tok->right->type == TNOCMD)
		return ;
	ft_bulitin(tok->right);
}
