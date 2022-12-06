/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:20:38 by kko               #+#    #+#             */
/*   Updated: 2022/12/07 02:02:42 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	writedoc(char *limiter, int *p)
{
	char	*line;

	set_signal(DOC);
	close(p[0]);
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
	close(p[1]);
	exit(0);
}

int	here_doc(char *limiter)
{
	pid_t	pid;
	int		p[2];
	int		stat;

	pipe(p);
	pid = fork();
	if (pid == 0)
		writedoc(limiter, p);
	else if (pid > 0)
		close(p[1]);
	waitpid(-1, &stat, 0);
	if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == 2)
			errno = -1;
	}
	return (p[0]);
}

// int	open_util(t_oper_type type, char *line)
// {
// 	int	fd;

// 	fd = 0;
// 	while (*line != ' ')
// 		line++;
// 	if (type == TOUT)
// 		fd = open(line, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	else if (type == TADDOUT)
// 		fd = open(line, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	else if (type == TIN) 
// 		fd = open(line, O_RDONLY);
// 	else if (type == TDOC) //히어독모드 추가예정
// 		fd = 0;
// 	return (fd);
// }

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
			printf("open err: %s: %d\n", find_redir(tmp->line + 1), errno);
			tok->fd_out = -1;
		}
	}
	else if (tmp->type == TADDOUT)
	{
		tok->fd_out = open(find_redir(tmp->line + 2), O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (tok->fd_out < 0)
		{
			printf("open err: %s: %d\n", find_redir(tmp->line + 2), errno);
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
			printf("open_in err: %s: %d\n", find_redir(tmp->line + 1), errno);
			tok->fd_in = -1;
		}
	}
	else if (tmp->type == TDOC)
	{
		set_signal(FORK);
		tok->fd_in = here_doc(find_redir(tmp->line + 2));
		set_signal(BASH);
	}
}

void	start_open(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while(tmp)
	{
		if (tmp->type == TOUT || tmp->type == TADDOUT)
		{
			if (tok->fd_out != -1)
				close(tok->fd_out);
			open_out(tok, tmp);
		}
		else if (tmp->type == TIN || tmp->type == TDOC)
		{
			if (tok->fd_in != -1)
				close(tok->fd_in);
			open_in(tok, tmp);
		}
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
		start_open(tok);
}