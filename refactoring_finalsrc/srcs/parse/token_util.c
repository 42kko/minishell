/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:46:42 by kko               #+#    #+#             */
/*   Updated: 2022/12/10 20:36:08 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokenstart(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*new_token(t_info *info)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		throw_error(MALLOC_ERR);
	new->type = NO_TYPE;
	new->cmd = NULL;
	new->line = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->left = NULL;
	new->right = NULL;
	new->comma_type = NO_COM;
	new->parent = NULL;
	new->info = info;
	new->fd_in = -1;
	new->fd_out = -1;
	new->err_flag_redir = 0;
	new->err_flag_syn = 0;
	new->token_type = 0;
	new->last_pid = 0;
	return (new);
}
