/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:39:32 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/02 20:18:50 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_push_index_until_space(char *line, int *index, \
t_brachek_type type, t_token *tok)
{
	(*index)++;
	if (type == O_BRACHEK)
		type = C_BRACHEK;
	while (line[*index] != 0)
	{
		if (ft_is_comma_brachek(line[*index]) == type)
			return ;
		(*index)++;
	}
	(*index)--;
	throw_error_syntax(SYNTAX_ERR, tok);
}

static int	start_is_seperator(char *line, t_token *tok)
{
	if (*line == '|' || *line == '&')
	{
		if (*(line + 1) != 0 && (*(line + 1) == '&' || *(line + 1) == '|'))
			return (2);
		if (*line == '&')
			throw_error_syntax(SYNTAX_ERR, tok);
		return (1);
	}
	return (0);
}

static int	seperate_token(char *line, t_token *tok)
{
	int	i;

	i = 0;
	if (start_is_seperator(line, tok))
		return (start_is_seperator(line, tok));
	while (line[i])
	{
		if (ft_is_comma_brachek(line[i]) != NO_BRACHEK)
			new_push_index_until_space(line, &i, \
			ft_is_comma_brachek(line[i]), tok);
		else if (line[i] == '|' || line[i] == '&')
			return (i);
		i++;
	}
	return (i);
}

static void	create_a_token(t_token **token, char **line, t_info *info)
{
	t_token	*tail;
	t_token	*new;
	int		i;
	char	*tmp;

	i = 0;
	tmp = *line;
	while (**line == ' ' && **line != 0)
		(*line)++;
	new = new_token(info);
	i = seperate_token(*line, new);
	new->line = ft_substr(*line, 0, i);
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

t_token	*init_token(char *line, t_info *info)
{
	t_token	*token;
	t_token	*temp;
	char	*tmp;

	token = 0;
	tmp = line;
	while (*line)
		create_a_token(&token, &line, info);
	error_hunter(token);
	free(tmp);
	if (token->err_flag_syn == 1)
		return (token);
	temp = token;
	while (temp)
	{
		set_type_remove_operator(&temp, &token);
		temp = temp->next;
	}
	check_redir_data(token);
	errno = 0;
	return (token);
}
