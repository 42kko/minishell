/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_index_about_comma.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:08:14 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/03 16:35:09 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pull_until_same_comma(char *str, int *i, t_comma_type flag)
{
	char	c;

	c = 0;
	if (flag == ONE_COM)
		c = '\'';
	if (flag == TWO_COM)
		c = '\"';
	if (str[*i] == c)
	{
		(*i)++;
		while (str[*i] != c && str[*i])
			(*i)++;
		if (str[*i] == c)
			(*i)++;
	}
}

void	push_index_until_space_or_oper(char *line, int *index)
{
	while (line[*index] != ' ' && line[*index] != \
	'\0' && check_operator(line[*index]) == NO_TYPE)
	{
		while (ft_is_comma(line[*index]) == NO_COM && line[*index] != \
		' ' && line[*index] != '\0' && ft_is_redir(line[*index]) == NO_TYPE)
			(*index)++;
		while (ft_is_comma(line[*index]) != NO_COM)
			pull_until_same_comma(line, index, ft_is_comma(line[*index]));
	}
}

void	count_redir(int *count, int *i, char *str)
{
	*count = *count + 1;
	*i = *i + 1;
	if (ft_is_redir(*str))
		*i = *i + 1;
}

int	count_space_out_of_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		while (ft_is_comma(str[i]) != NO_COM)
			pull_until_same_comma(str, &i, ft_is_comma(str[i]));
		if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
		}
		else if (ft_is_redir(str[i]))
		{
			count_redir(&count, &i, &str[i]);
		}
		else if (str[i])
			i++;
	}
	i = 0;
	return (count);
}
