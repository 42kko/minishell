/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:20:38 by kko               #+#    #+#             */
/*   Updated: 2022/12/08 18:03:08 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	writedoc(char *limiter, int *p, t_token *tok)
{
	char	*line;

	set_signal(DOC);
	close_util(p[0], tok);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
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
	pid = fork();
	if (pid == -1)
		err_msg("fork err", tok, 0);
	else if (pid == 0)
		writedoc(limiter, p, tok);
	else if (pid > 0)
		close_util(p[1], tok);
	waitpid(-1, &stat, 0);
	if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == 2)
			errno = -1;
	}
	return (p[0]);
}

char	*find_redir(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp == ' ')
		tmp++;
	return (tmp);
}


void	open_out(t_token *tok, t_token *tmp)
{
	if (tmp->type == TOUT)
	{
		tok->fd_out = open(find_redir(tmp->line + 1), O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (tok->fd_out < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 1));
			tok->fd_out = -1;
		}
	}
	else if (tmp->type == TADDOUT)
	{
		tok->fd_out = open(find_redir(tmp->line + 2), O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (tok->fd_out < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 2));
			tok->fd_out = -1;
		}
	}
}

void	open_in(t_token *tok, t_token *tmp)
{
	if (tmp->type == TIN)
	{
		tok->fd_in = open(find_redir(tmp->line + 1), O_RDONLY);
		if (tok->fd_in < 0)
		{
			err_msg("open err", tok, find_redir(tmp->line + 1));
			tok->fd_in = -1;
			tok->parent->errn = 1;
		}
	}
	else if (tmp->type == TDOC)
	{
		set_signal(FORK);
		tok->fd_in = here_doc(find_redir(tmp->line + 2), tok);
		set_signal(BASH);
	}
}

void	close_util(int fd, t_token *tok)
{
	if (close(fd) < 0)
		err_msg("close err", tok, 0);
}

void	start_open(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	errno = 0;
	while(tmp)
	{
		if (tmp->type == TOUT || tmp->type == TADDOUT)
		{
			if (tok->fd_out != -1)
				close_util(tok->fd_out, tok);
			open_out(tok, tmp);
		}
		else if (tmp->type == TIN || tmp->type == TDOC)
		{
			if (tok->fd_in != -1)
				close_util(tok->fd_in, tok);
			open_in(tok, tmp);
		}
		else if (errno != 0)
			break ;
		tmp = tmp->next;
	}
}

void	open_redir(t_token *tok)
{
	if (tok == 0)
		return ;
	open_redir(tok->left);
	open_redir(tok->right);
	if (tok->type == TOUT || tok->type == TADDOUT || \
	tok->type == TIN || tok->type == TDOC)
	{
		start_open(tok);
		if (errno != 0)
			tok->parent->errn = -1;
	}
}