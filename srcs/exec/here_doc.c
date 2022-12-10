/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:56:41 by kko               #+#    #+#             */
/*   Updated: 2022/12/10 13:16:52 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	writedoc(char *limiter, int *p, t_token *tok)
{
	char	*line;

	set_signal(DOC);
	close_util(p[0], tok);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (*line == '\0')
			write(p[1], "\n", 1);
		else if (*line != '\n' && \
		ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		write(p[1], line, ft_strlen(line));
		write(p[1], "\n", 1);
		free(line);
		line = NULL;
	}
	close_util(p[1], tok);
	exit(0);
}

int	here_doc(char *limiter, t_token *tok)
{
	pid_t	pid;
	int		p[2];
	int		stat;

	if (pipe(p) < 0)
		err_msg("pipe err", tok, 0);
	pid = fork_util(tok);
	if (pid == 0)
		writedoc(limiter, p, tok);
	else if (pid > 0)
		close_util(p[1], tok);
	waitpid(-1, &stat, 0);
	if (WIFSIGNALED(stat))
	{
		close(p[0]);
		tok->info->exit_num = 130;
		tok->parent->err_flag_redir = -1;
	}
	return (p[0]);
}
