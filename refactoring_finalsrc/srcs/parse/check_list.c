/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:42:53 by kko               #+#    #+#             */
/*   Updated: 2022/12/09 00:24:51 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redir_data(t_token *tok)
{
	int	i;

	while (tok)
	{
		i = 0;
		if (tok->type == TDOC || tok->type == TADDOUT || \
		tok->type == TIN || tok->type == TOUT)
		{
			while (tok->line[i])
			{
				if (tok->line[i] != '<' && tok->line[i] != '>' && \
				tok->line[i] != ' ' && tok->line[i] != '\0')
					break ;
				i++;
			}
			if (tok->line[i] == '\0')
				throw_error_syntax(SYNTAX_ERR, tok);
		}
		tok = tok->next;
	}
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

t_oper_type	check_operator(char c)
{
	if (c == '|')
		return (TPIPE);
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
		return (TPIPE);
	else if (c == '&')
		return (TAND);
	else if (c == '<')
		return (TIN);
	else if (c == '>')
		return (TOUT);
	else if (c == '\'')
		return (O_COM);
	else if (c == '\"')
		return (T_COM);
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
