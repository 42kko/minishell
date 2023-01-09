/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_com.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:52:27 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/03 13:14:13 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_tok_cmd(t_token *tok, int i)
{
	int		j;
	char	*ret;

	j = 0;
	while (tok->line[i + j] != 0 && tok->line[i + j] != ' ')
		j++;
	ret = (char *)malloc(sizeof(char) * j + 1);
	ret[j--] = 0;
	while (j >= 0)
	{
		ret[j] = tok->line[i + j];
		j--;
	}
	return (ret);
}

void	push_index_com(char *line, int *idx)
{
	t_comma_type	tmp;

	tmp = ft_is_comma(line[*idx]);
	(*idx)++;
	while (ft_is_comma(line[*idx]) != tmp)
		(*idx)++;
}

void	jump_redir(char *line, int *idx, int i)
{
	while (line[*idx] == ' ')
	{
		i = 1;
		(*idx)++;
	}
	if (i == 1)
		(*idx)--;
	if (ft_is_redir(line[*idx]) == NO_DIREC)
		return ;
	(*idx)++;
	if (ft_is_redir(line[*idx]))
	{
		(*idx)++;
	}
	while (line[*idx] == ' ')
		(*idx)++;
	while (line[*idx] && line[*idx] != ' ')
	{
		if (ft_is_comma(line[*idx]))
			push_index_com(line, idx);
		(*idx)++;
	}
	while (line[*idx] == ' ')
		(*idx)++;
}

char	*get_tok_cmd(t_token *tok, int idx)
{
	int		i;
	char	*ret;

	i = 0;
	jump_redir(tok->line, &i, 0);
	while (tok->line[i] && idx != 0)
	{
		jump_redir(tok->line, &i, 0);
		if (tok->line[i] == '\"' || tok->line[i] == '\'')
		{
			i++;
			while (tok->line[i] != '\"' && tok->line[i] != '\'')
				i++;
		}
		if (tok->line[i] == ' ')
			idx--;
		i++;
	}
	ret = set_tok_cmd(tok, i);
	return (ret);
}

int	com_wild(t_token *tok, int j)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_tok_cmd(tok, j);
	if (ft_strchr(tmp, '*') == 0)
		return (free_wild(tmp, 0));
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			i++;
			while (tmp[i] != '\"' && tmp[i] != '\'')
				i++;
		}
		if (tmp[i] == '*')
			return (free_wild(tmp, 1));
		i++;
	}
	return (free_wild(tmp, 0));
}
