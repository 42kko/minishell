/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:45:48 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/23 19:16:31 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func(char *s)
{
	printf("list : '%s'\n", s);
}

void	fc(int s)
{
	printf("type : '%d'\n", s);
}


void	ft_tokeniter(t_token *lst, void (*f)(char *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->line);
		fc(lst->type);
		lst = lst->next;
	}	
}
