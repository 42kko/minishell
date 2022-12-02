/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:43:50 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/02 17:10:41 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

void	check_subshells(t_token **token, int i)
{
	i = 0;
	(*token)->type = TBRACH;
	if ((*token)->line[0] != '(')
		throw_error_syntax(SYNTAX_ERR, *token);
	else if ((*token)->line[0] == '(')
		new_push_index_until_space((*token)->line + i, &i, O_BRACHEK, *token);
	i++;
	while ((*token)->line[i])
	{
		if (check_redir((*token)->line[i]))
		{
			while ((*token)->line[i])
			{
				if ((*token)->line[i] == '\0')
					return ;
				else if ((*token)->line[i] == ' ')
					break ;
				i++;
			}
		}
		if (check_redir((*token)->line[i]) == 0 && \
		((*token)->line[i] != '\0' && (*token)->line[i] != ' '))
			throw_error_syntax(SYNTAX_ERR, *token);
		i++;
	}
}

int	have_brachek(char *line, t_token *tok)
{
	int	cnt;

	cnt = 0;
	while (*line)
	{
		if (*line == '(')
			cnt++;
		line++;
	}
	if (cnt > 1)
		throw_error_syntax(SYNTAX_ERR, tok);
	return (cnt);
}

void	check_type(t_token **token)
{
	set_type(token, '|', TPIPE, TOR);
	set_type(token, '&', NO_TYPE, TDAND);
	set_type(token, '<', TIN, TDOC);
	set_type(token, '>', TOUT, TADDOUT);
	if ((*token)->type == NO_TYPE)
		throw_error_syntax(SYNTAX_ERR, *token);
}

void	set_type(t_token **token, char oper, t_oper_type one, t_oper_type two)
{
	char	*line;

	line = (*token)->line;
	if (line[0] == oper)
	{
		if (line[1] == 0 || check_operator(line[1]) == 0)
			(*token)->type = one;
		else if (line[1] == oper && check_operator(line[2]) == 0)
			(*token)->type = two;
	}
}

t_oper_type	check_operator(char c)
{
	if (c == '|')
		return(TPIPE);
	else if (c == '&')
		return (TAND);
	else if (c == '<')
		return (TIN);
	else if (c == '>')
		return (TOUT);
	else if (c == ';')
		return(TSEMI);
	return (NO_TYPE);
}

t_oper_type	first_check_operator(char c)
{
	if (c == '|')
		return (TPIPE);
	else if (c == '&')
		return (TAND);
	else if (c == ';')
		return (TSEMI);
	return (NO_TYPE);
}