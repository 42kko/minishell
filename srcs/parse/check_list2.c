/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:42:53 by kko               #+#    #+#             */
/*   Updated: 2022/12/09 02:30:14 by seokchoi         ###   ########.fr       */
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
