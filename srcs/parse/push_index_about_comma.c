/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_index_about_comma.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:08:14 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 00:36:37 by kko              ###   ########.fr       */
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
		else if (str[i])
			i++;
	}
	return (count);
}
