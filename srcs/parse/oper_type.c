/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:43:50 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/07 10:42:19 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	cnt_redir(char *line, t_token **tok)
{
	if (line[1] == '\0')
		return (1);
	else if (line[0] == '<' && line[1] == '<')
		return (2);
	else if (line[0] == '>' && line[1] == '>')
		return (2);
	else if (line[1] != '\0')
		return (1);
	throw_error_syntax(SYNTAX_ERR, *tok);
	return (1);
}

int	push_index(char *line, int *i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (line[j] == '\0')
		return (-1);
	while (line[j] == ' ' && line[j] != '\0')
		j++;
	if (line[j] == '\0')
		return (-1);
	while (line[j + k] != ' ' && line[j + k] != '\0' && \
	check_redir(line[j + k]) == 0)
		k++;
	if (k == 0)
		return (-1);
	return (*i += j + k - 1);
}

void	check_subshells(t_token **token, int i)
{
	i = 0;
	if ((*token)->line[0] == '(')
		new_push_index_until_space((*token)->line + i, &i, O_BRACHEK, *token);
	i++;
	while ((*token)->line[i])
	{
		if (check_redir((*token)->line[i]))
		{
			i += cnt_redir((*token)->line + i, token);
			if (push_index((*token)->line + i, &i) < 0)
			{
				throw_error_syntax(SYNTAX_ERR, *token);
				return ;
			}
		}
		else if (check_redir((*token)->line[i]) == 0 && \
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
	return (NO_TYPE);
}

t_oper_type	check_operator_for_env(char c)
{
	if (c == '|')
		return(TPIPE);
	else if (c == '&')
		return (TAND);
	else if (c == '<')
		return (TIN);
	else if (c == '>')
		return (TOUT);
	else if (c == '\'')
		return(O_COM);
	else if (c == '\"')
		return(T_COM);
	return (NO_TYPE);
}

t_oper_type	first_check_operator(char c)
{
	if (c == '|')
		return (TPIPE);
	else if (c == '&')
		return (TAND);
	return (NO_TYPE);
}