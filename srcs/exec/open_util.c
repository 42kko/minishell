/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:55:31 by kko               #+#    #+#             */
/*   Updated: 2022/12/10 13:16:38 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_redir(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp == ' ')
		tmp++;
	return (tmp);
}

void	close_util(int fd, t_token *tok)
{
	if (close(fd) < 0)
		err_msg("close err", tok, 0);
}

int	fork_util(t_token *tok)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		err_msg("frok err", tok, 0);
	return (pid);
}
