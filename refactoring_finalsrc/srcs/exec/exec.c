/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:37:52 by kko               #+#    #+#             */
/*   Updated: 2023/01/08 12:54:13 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	identify_built_exec(t_token *tok)
{
	if (tok->type != TCMD)
		return (-1);
	if (ft_strncmp(tok->cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "$?", 3) == 0)
		return (1);
	else
		return (0);
}

void	exec(t_token *tok)
{
	pid_t	pid;
	int		stat;

	pid = fork_util(tok);
	if (pid == 0)
	{
		tok->info->exit_num = 0;
		set_signal(DFL);
		tcsetattr(STDIN_FILENO, TCSANOW, tok->info->old_term);
		errno = 0;
		if (tok->left->type != NO_REDIR)
			io_ctl_cmd(tok->left);
		if (tok->right->type == TNOCMD)
			exit (0);
		add_path(tok->right);
		execve(tok->right->cmd[0], tok->right->cmd, \
		get_env_arr(tok->info->env_list));
		exit(126);
	}
	else if (pid > 0)
		wait(&stat);
	if (WIFEXITED(stat))
		tok->info->exit_num = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
		tok->info->exit_num = WTERMSIG(stat) + 128;
}
