/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:43:50 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 19:44:57 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
