/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:45:48 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/24 20:14:43 by kko              ###   ########.fr       */
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
