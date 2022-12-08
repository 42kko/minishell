/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:44:32 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 02:30:29 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_token_line(t_token **token)
{
	int		i;
	char	*new_line;
	char	*tmp;

	i = 1;
	if (!(*token)->cmd)
		return (NULL);
	new_line = ft_strdup((*token)->cmd[0]);
	if (!new_line)
		return (NULL);
	while ((*token)->cmd[i])
	{
		tmp = new_line;
		new_line = ft_strjoin_space(new_line, (*token)->cmd[i]);
		free(tmp);
		i++;
	}
	return (new_line);
}

void	sort_token_order(t_token **token, t_token **first, \
t_token *redir_token)
{
	t_token	*redir_last;
	t_token	*tmp_prev_token;

	tmp_prev_token = (*token)->prev;
	if (tmp_prev_token && redir_token)
	{
		tmp_prev_token->next = redir_token;
		redir_token->prev = tmp_prev_token;
		redir_last = ft_tokenlast(redir_token);
		(*token)->prev = redir_last;
		redir_last->next = (*token);
	}
	else if (redir_token)
	{
		redir_last = ft_tokenlast(redir_token);
		redir_last->next = (*token);
		(*token)->prev = redir_last;
		*first = redir_token;
	}
}
