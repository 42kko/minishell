/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:36:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/26 01:43:47 by seokchoi         ###   ########.fr       */
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

void	push_index_until_space_or_oper(char *line, int *index) // " ' 을 제외 시킨 문자열 인덱스를 이동시켜준다. 
{
	while (line[*index] != ' ' && line[*index] != '\0' && check_operator(line[*index]) == NO_TYPE)
	{
		while (ft_is_comma(line[*index]) == NO_COM && line[*index] != ' ' && line[*index] != '\0' && ft_icheck_operators_redir(line[*index]) == NO_TYPE)
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

char	*change_s1_to_s2_in_str(char *s1, char*s2, char *str) // s1은 $을 포함한 것이다.
{
	char	*changed;
	int		s1_len;
	int		s2_len;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	changed = malloc(sizeof(char) * (ft_strlen(str) - s1_len + s2_len + 1));
	while (str[i] && str[i] != '$')
		changed[k++] = str[i++];
	while ()
	{
		
	}
	i += s1_len;
	return (changed);
}

char	*get_env_key(char *line)
{
	
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
			{
				if (type == TWO_COM && s[i] == '$')
				{
					push_index_until_space_or_oper();
				}
				str[j++] = s[i++];
			}
			if (s[i])
				i++;
		}
		else
		{
			// $가 들어올 경우
			str[j++] = s[i++];
		}
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
