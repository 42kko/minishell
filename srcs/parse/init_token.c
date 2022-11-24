/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:39:32 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/24 14:34:51 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_push_index_until_space(char *line, int *index, t_brachek_type type)
{
	if (type == O_BRACHEK)
		type = C_BRACHEK;
	while (line[*index] != '\0')
	{
		if (ft_is_comma_brachek(line[*index]) == type)
		{
			return ;
		}
		(*index)++;
	}
	exit(0); //아래 사항대로 수정할것
	// err_msg //해당 콤마를 못찾으면 그대로 syntax에러
}

// void	push_index_until_space(char *line, int *index)
// {
// 	while (line[*index] != ' ' && line[*index] != '\0')
// 	{
// 		while (ft_is_comma(line[*index]) == NO_COM && line[*index] != ' ' && line[*index] != '\0')
// 			(*index)++;
// 		while (ft_is_comma(line[*index]) != NO_COM)
// 			pull_until_same_comma(line, index, ft_is_comma(line[*index]));
// 	}
// }

t_token *ft_tokenstart(t_token *lst)
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

void init_token(char *line)
{
	t_token	*token;

	char *tmp;

	token = 0;
	int i = 0;

	tmp = line;
	while (*line)
		create_a_token(&token, &line);
	free(tmp);

	t_token *temp;
	temp = token;
	while (temp)
	{
		set_type_remove_operator(&temp);
		temp = temp->next;
	}
	ft_tokeniter(token, func);
}
