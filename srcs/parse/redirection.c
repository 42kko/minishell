/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:59:30 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/23 21:44:55 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TOUT, //>
// TADDOUT, //>>
// TIN, //<
// TDOC, //<<

void	attach_redir_token(t_token	**redir_token, t_token **token, int index)
{
	t_token *new;
	t_token *tmp;

	tmp = *redir_token;
	new = new_token();
	new->line = ft_strdup((*token)->cmd[index]); // 복사
	check_type(&new);
	if (!new->line)
		throw_error(MALLOC_ERR);
	if (!(*redir_token))
	{
		(*redir_token) = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	devide_redir_cmd(t_token **token)
{
	t_token	*tmp_prev_token;
	t_token	*tmp_next_token;
	t_token	*redir_token;
	char	*tmp;
	int		left;
	int		right;
	char	**new_cmd_arr;
	
	tmp_prev_token = (*token)->prev;
	tmp_next_token = (*token)->next;
	left = 0;
	right = 0;
	redir_token = NULL;
	while ((*token)->cmd[left])
	{
		if (ft_is_redir((*token)->cmd[left][0]) != NO_DIREC)
		{
			attach_redir_token(&redir_token, token, left);
			right++;
		}
		left++;
	}
	// ft_tokeniter(redir_token, func);
	new_cmd_arr = malloc(sizeof(char *) * (get_sec_arr_len((*token)->cmd) - right + 1));
	if (!new_cmd_arr)
		throw_error(MALLOC_ERR);
	right = 0;
	left = 0;
	while ((*token)->cmd[left])
	{
		if (ft_is_redir((*token)->cmd[left][0]) == NO_DIREC)
		{
			new_cmd_arr[right] = ft_strdup((*token)->cmd[left]);
			if (!new_cmd_arr[right])
				throw_error(MALLOC_ERR);
			right++;
		}
		left++;
	}
	new_cmd_arr[right] = NULL;
	free_sec_arr((*token)->cmd);
	(*token)->cmd = new_cmd_arr;
	if (tmp_prev_token)
	{
		tmp_prev_token->next = redir_token;
		redir_token->next = (*token);
	}
	else
	{
		(*token)->prev = redir_token;
		redir_token->next = (*token);
		*token = redir_token;
	}
}

void	set_type_remove_operator(t_token **token)
{
	if (check_operator((*token)->line[0]) == TPIPE || check_operator((*token)->line[0]) == TAND)
	{
		check_type(token);
	}
	else
	{
		set_cmd(token);
		devide_redir_cmd(token);
		// int i = 0;
		// while ((*token)->cmd[i])
		// {
		// 	printf("%d : \'%s\'\n", i, (*token)->cmd[i]);
		// 	i++;
		// }
	}
}
