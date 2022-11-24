/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:36:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/25 00:41:55 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pull_until_same_comma(char *str, int *i, t_comma_type flag)
{
	char c;

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

void	push_index_until_space(char *line, int *index)
{
	while (line[*index] != ' ' && line[*index] != '\0')
	{
		while (ft_is_comma(line[*index]) == NO_COM && line[*index] != ' ' && line[*index] != '\0')
			(*index)++;
		while (ft_is_comma(line[*index]) != NO_COM)
			pull_until_same_comma(line, index, ft_is_comma(line[*index]));
	}
}

int	count_space_out_of_comma(char *str) // \", \' 을 스킵하고 ' ' 띄어쓰기를 찾아주는 함수
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

char	*ft_strdup_without_check_comma(char *s, int start, int len)
{
	char			*str;
	int				i;
	int				j;
	t_comma_type	type;

	i = start;
	j = 0;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		throw_error(MALLOC_ERR);
	while (s[i] &&  j < len && i < start + len)
	{
		type = ft_is_comma(s[i]);
		if (type)
		{
			i++;
			while (s[i] && ft_is_comma(s[i]) != type && j < len)
				str[j++] = s[i++];
			if (s[i])
				i++;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}

int	token_list_len(t_token *token)
{
	int	len;

	len = 0;
	while (token)
	{
		len++;
		token = token->next;
	}
	return (len);
}
