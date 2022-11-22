/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:59:30 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/22 21:21:17 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	attach_redir_token(t_token	**redir_token, t_token **token, int index)
// {
// 	t_token *new;
	
// 	new = new_token();
// 	new->line = (*token)->cmd[index];
// 	if (!redir_token)
// 		(*redir_token) = new;
// 	while ((*redir_token)->next)
// 		(*redir_token) = (*redir_token)->next;
// 	(*redir_token)->next = new;
// }

// void	devide_redir_cmd(t_token **token)
// {
// 	t_token	*tmp_next_token;
// 	t_token	*redir_token;
// 	char	*tmp;
// 	int		left;
// 	int		right;
	
// 	printf("asdfasdfasdfasdfsdf\n");
// 	tmp_next_token = (*token)->next;
// 	left = 0;
// 	right = 0;
// 	redir_token = NULL;
// 	while ((*token)->cmd[left])
// 	{
// 		printf("홀리몰리\n");
// 		if (ft_is_comma((*token)->cmd[left][0]) != NO_TYPE)
// 			attach_redir_token(&redir_token, token, left);
// 		left++;
// 	}
// 	ft_tokeniter(redir_token, func);
// 	while ((*token)->cmd[right])
// 		right++;
// 	right--;
// 	while (left < right) // 
// 	{
// 		while (left < right) // redir을 찾는다.
// 		{
// 			if (ft_is_comma((*token)->cmd[left][0]) != NO_TYPE)
// 				break;
// 			left++;
// 		}
// 		while (left < right) // 앞에 redir이 있는 cmd을 찾는다.
// 		{
// 			if (ft_is_comma((*token)->cmd[left][0]) == NO_TYPE)
// 				break;
// 			right--;
// 		}
// 	}
// }

void	set_type_remove_operator(t_token **token)
{
	if (check_operator((*token)->line[0]) == TPIPE || check_operator((*token)->line[0]) == TAND)
	{
		check_type(token);
	}
	else
	{
		set_cmd(token);
		// devide_redir_cmd(token);
		int i = 0;
		while ((*token)->cmd[i])
		{
			printf("%d : \'%s\'\n", i, (*token)->cmd[i]);
			i++;
		}
	}
}