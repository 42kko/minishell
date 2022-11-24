/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:43:50 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/23 17:53:36 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_type(t_token **token)
{
	set_type(token, '|', TPIPE, TOR);
	set_type(token, '&', NO_TYPE, TDAND);
	set_type(token, '<', TIN, TDOC);
	set_type(token, '>', TOUT, TADDOUT);
	if ((*token)->type == NO_TYPE)
		throw_error(SYNTAX_ERR);
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
	else if (c == '(')
		return (TOBRACH);
	else if (c == ')')
		return(TCBRACH);
	return (NO_TYPE);
}
