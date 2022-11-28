/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:36:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/29 00:07:24 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_comma_check_env(t_token **token, t_keys **keys,t_parse_tmp *tmp)
{
	int		*i;
	int		*j;
	char	*s;

	i = tmp->i;
	j = tmp->j;
	s = tmp->s;
	if (tmp->type)
	{
		(*i)++;
		while (s[(*i)] && ft_is_comma(s[(*i)]) != tmp->type && (*j) < tmp->len)
		{
			if (tmp->type == TWO_COM && s[(*i)] == '$') // comma 타입중에서 " 일때만 환경변수 처리
				check_env_record(token, keys, (*i));
			tmp->str[(*j)++] = s[(*i)++];
		}
		if (s[(*i)])
			(*i)++;
	}
	else
	{
		if (s[(*i)] == '$') // " 안에있지 않은 환경변수의 경우에는 oper도 포함시킨다.
			check_env_record(token, keys, (*i));
		tmp->str[(*j)++] = s[(*i)++];
	}
}

static t_parse_tmp	*init_parse_tmp(int *i, int *j, char *s, char *str)
{
	t_parse_tmp		*tmp;

	tmp = calloc(sizeof(t_parse_tmp), 1);
	if (!tmp)
		throw_error(MALLOC_ERR);
	tmp->i = i;
	tmp->j = j;
	tmp->str = str;
	tmp->s = s;
	return (tmp);
}

char	*ft_strdup_without_check_comma(t_token **token, char *s, int start, int len) // " 안에 있는 환경변수를 바꿔줄 수  있있어야한다.
{
	char			*str;
	int				i;
	int				j;
	t_comma_type	type;
	t_keys			*keys;
	t_parse_tmp		*tmp;

	i = start;
	j = 0;
	keys = NULL;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		throw_error(MALLOC_ERR);
	tmp = init_parse_tmp(&i, &j, s, str);
	tmp->len = len;
	while (s[i] &&  j < len && i < start + len) // 만약 key를 value로 바꾼다면 str 동적할당을 value에 맞게 해야한다.
	{
		type = ft_is_comma(s[i]);
		tmp->type = type;
		delete_comma_check_env(token, &keys, tmp);
	}
	str[j] = '\0';
	str = change_key_to_value(str, keys);
	free(tmp);
	if (keys)
		free_keys(keys);
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
