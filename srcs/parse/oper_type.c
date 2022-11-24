/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:43:50 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/24 18:33:32 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_subshells(t_token **token)
{
	int	i;
	int	flag;

	i = 0;
	while ((*token)->line[i])
	{
		if ((*token)->line[i] == '(')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	i == 0;
	while ((*token)->line[i] && flag == 1)
	{
		if ((*token)->line[i] != '(' && ((*token)->line[i] != ' ' || (*token)->line[i] != 0))
			throw_error(SYNTAX_ERR);
		i++;
	}
			new_push_index_until_space((*token)->line + i, &i, O_BRACHEK);
}

void	check_type(t_token **token)
{
	check_subshells(token);
	set_type(token, '|', TPIPE, TOR);
	set_type(token, '&', NO_TYPE, TDAND);
	set_type(token, '(', NO_TYPE, TDAND);
	if ((*token)->type == NO_TYPE)
		throw_error(SYNTAX_ERR);
}

void	set_type(t_token **token, char oper, t_oper_type one, t_oper_type two)
{
	char	*line;

	line = (*token)->line;
	if (line[0] == oper)
	{
		if (line[1] == 0 || check_operator(line[1]) == oper)
			(*token)->type = one;
		else if (line[1] == oper && check_operator(line[2]) == oper)
			(*token)->type = two;
	}
}

t_oper_type	check_operator(char c)
{
	if (c == '|')
		return(TPIPE);
	else if (c == '&')
		return (TAND);
	else if (c == ';')
		return (TSEMI);
	else if (c == '(')
		return (TOBRACH);
	else if (c == ')')
		return(TCBRACH);
	return (NO_TYPE);
}
