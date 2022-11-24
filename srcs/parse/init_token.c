/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:39:32 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/25 03:41:10 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_push_index_until_space(char *line, int *index, t_brachek_type type)
{
	(*index)++;
	if (type == O_BRACHEK)
		type = C_BRACHEK;
	while (line[*index] != '\0')
	{
		if (ft_is_comma_brachek(line[*index]) == type)
			return ;
		(*index)++;
	}
	throw_error(SYNTAX_ERR);
}

t_token	*ft_tokenstart(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

int	start_is_seperator(char *line)
{
	t_brachek_type	type;

	if (*line == '|' || *line == '&' || *line == ';')
	{
		if (*(line + 1) != 0 && (*(line + 1) == '&' || *(line + 1) == '|'))
			return (2);
		return (1);
	}
	return (0);
}

t_token	*new_token(void)
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
	return (new);
}

int	seperate_token(char *line)
{
	int	i;

	i = 0;
	if (start_is_seperator(line))
		return (start_is_seperator(line));
	while (line[i])
	{
		if (ft_is_comma_brachek(line[i]) != NO_BRACHEK)
			new_push_index_until_space(line, &i, ft_is_comma_brachek(line[i]));
		else if (line[i] == '|' || line[i] == '&' || line[i] == ';')
			return (i);
		i++;
	}
	return (i);
}

void	create_a_token(t_token **token, char **line)
{
	t_token	*tail;
	t_token	*new;
	int		i;
	char	*tmp;

	i = 0;
	tmp = *line;
	while (**line == ' ' && **line != 0)
		(*line)++;
	new = new_token();
	i = seperate_token(*line);
	new->line = ft_substr(*line, 0,i);
	(*line) += i;
	if (*token == 0)
		(*token) = new;
	else
	{
		tail = ft_tokenlast(*token);
		new->prev = tail;
		tail->next = new;
	}
}

t_token *next_token(t_token *token)
{
	token = token->next;
	token->prev->next = 0;
	token->prev = 0;
	return (token);
}

t_token *tail_token(t_token *token)
{
	token = token->prev;
	token->next->prev = 0;
	token->next = 0;
	while (token->prev)
		token = token->prev;
	return (token);
}

void	select_oper(t_token *tok, t_oper_type *oper1, \
t_oper_type *oper2, t_oper_type *oper3)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == TDAND || tmp->type == TOR || tmp->type == TSEMI)
		{
			*oper1 = TDAND;
			*oper2 = TOR;
			*oper3 = TSEMI;
			return ;
		}
		tmp = tmp->next;
	}
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == TPIPE)
		{
			*oper1 = TPIPE;
			return ;
		}
		tmp = tmp->next;
	}
}

t_token	*get_tree(t_token *token)
{
	t_token		*tmp;
	t_oper_type	oper1;
	t_oper_type	oper2;
	t_oper_type	oper3;

	oper1 = 0;
	oper2 = 0;
	oper3 = 0;
	tmp = token;
	select_oper(token, &oper1, &oper2, &oper3);
	while (tmp)
	{
		if (tmp->type == oper1 || tmp->type == oper2 || tmp->type == oper3)
		{
			tmp->left = get_tree(tail_token(tmp));
			tmp->right = get_tree(next_token(tmp));
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (token);
}

void	viewtree(t_token *tok)
{
	if (tok == 0)
		return ;
	printf("tree : %s\n", tok->line);
	viewtree(tok->left);
	viewtree(tok->right);
}

void init_token(char *line)
{
	t_token	*token;
	char	*tmp;
	t_token	*temp;

	token = 0;
	tmp = line;
	while (*line)
		create_a_token(&token, &line);
	free(tmp);
	temp = token;
	while (temp)
	{
		set_type_remove_operator(&temp, &token);
		temp = temp->next;
	}
	token = get_tree(token);
	viewtree(token);
}
