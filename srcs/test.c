/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:45:48 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/30 10:16:20 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_line(t_token *lst)
{
	int i;
	t_oper_type s;

	i = 0;
	s = lst->type;
	if (s == TPIPE)
		printf("line : %s | ", lst->line); // |
	else if (s == TOR)
		printf("line : %s | ", lst->line); // ||
	else if (s == TAND)
		printf("line : %s | ", lst->line); // &
	else if (s == TDAND)
		printf("line : %s | ", lst->line); // &&
	else if (s == TIN)
		printf("line : %s | ", lst->line); // <
	else if (s == TOUT)
		printf("line : %s | ", lst->line); // > 
	else if (s == TSEMI)
		printf("line : %s | ", lst->line); // ;
	else if (s == TADDOUT)
		printf("line : %s | ", lst->line); // <<
	else if (s == TDOC)
		printf("line : %s | ", lst->line); // >>
	else if (s == TCMD)
	{
		printf("cmd : ");
		while (lst->cmd[i])
		{
			printf("%s ", lst->cmd[i]); // cmd
			i++;
		}
		printf("| ");
	}
	printf("line : NO_TYPE | ");
}

void	printf_type(t_oper_type s)
{
	if (s == TPIPE)
		printf("type : TPIPE | "); // |
	else if (s == TOR)
		printf("type : TOR | "); // ||
	else if (s == TAND)
		printf("type : TAND | "); // &
	else if (s == TDAND)
		printf("type : TDAND | "); // &&
	else if (s == TIN)
		printf("type : TIN | "); // <
	else if (s == TOUT)
		printf("type : TOUT | "); // > 
	else if (s == TSEMI)
		printf("type : TSEMI | "); // ;
	else if (s == TADDOUT)
		printf("type : TADDOUT | "); // <<
	else if (s == TDOC)
		printf("type : TDOC | "); // >>
	else if (s == TCMD)
		printf("type : TCMD | "); // cmd
	else if (s == NO_TYPE)
		printf("type : NO_TYPE | "); // no type
}

void	func(char *s)
{
	printf("list : '%s'\n", s);
}

void	show_list_type_data(t_token *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	while (lst)
	{
		printf("%d | ", i);
		printf_type(lst->type);
		printf_line(lst);
		lst = lst->next;
		printf("\n");
		i++;
	}
}

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
	viewtree(tok->left);
	if (tok->left)
		tok->left->parent = tok;
	if (tok->right)
		tok->right->parent = tok;
	printf("tree : %s\n", tok->line);
	viewtree(tok->right);
}
