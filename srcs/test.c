/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:45:48 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/25 08:18:27 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokeniter(t_token *lst)
{
	while (lst)
	{
		printf("list : %s - %d\n", lst->line, lst->type);
		lst = lst->next;
	}
}

void	viewtree(t_token *tok)
{
	if (tok == 0)
		return ;
	printf("tree : %s\n", tok->line);
	viewtree(tok->left);
	viewtree(tok->right);
}
