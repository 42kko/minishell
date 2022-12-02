/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:34:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/02 23:37:03 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	push_index_len_redirection(char *line, int *index)
{
	int			flag;
	t_oper_type	type;

	flag = 0;
	type = check_operator(line[*index]);
	(*index)++;
	if (check_operator(line[*index]) == type)
		(*index)++;
	else if (check_operator(line[*index]) != NO_TYPE)
		throw_error(SYNTAX_ERR);
	while (line[*index] == ' ')
		(*index)++;
	push_index_until_space_or_oper(line, &(*index));
}

int	check_is_start_cmd(char *line, int *right)
{
	if (line[(*right)] == ' ' || line[(*right)] == '\0' || \
	ft_is_redir(line[(*right)]) != NO_DIREC)
		return (1);
	return (0);
}

static int	cut_cmd(t_token **token, char **arr, int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	if (line[(*right)] == '<' || line[(*right)] == '>')
	{
		push_index_len_redirection(line, &(*right), *token);
		*arr = cpy_wout_com(token, line, (*left), (*right) - (*left));
		while (line[(*right)] == ' ')
			(*right)++;
		return (1);
	}
	else
	{
		push_index_until_space_or_oper(line, &(*right));
		if (check_is_start_cmd(line, right))
		{
			*arr = cpy_wout_com(token, line, (*left), (*right) - (*left));
			while (line[(*right)] == ' ')
				(*right)++;
			return (1);
		}
		else if (line[(*right)])
			(*right)++;
	}
	return (0);
}

char	**ft_split_cmd(t_token **token, char *line)
{
	char	**arr;
	int		left;
	int		right;
	int		i;
	int		check_env;

	check_env = 0;
	i = 0;
	arr = malloc(sizeof(char *) * (count_space_out_of_comma(line) + 1));
	if (!arr)
		throw_error(MALLOC_ERR);
	right = 0;
	while (line[right])
	{
		left = right;
		if (cut_cmd(token, &arr[i], &left, &right))
			i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	set_cmd(t_token **token)
{
	(*token)->type = TCMD;
	(*token)->cmd = ft_split_cmd(token, (*token)->line);
}
