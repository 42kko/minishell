/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:36:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/30 13:01:09 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*cpy_wout_com(t_token **token, char *s, int start, int len) // " 안에 있는 환경변수를 바꿔줄 수  있있어야한다.
{
	char			*str;
	int				i;
	int				j;
	t_keys			*keys;
	t_parse_tmp		*tmp;

	i = start;
	j = 0;
	keys = NULL;
	str = malloc_str(len);
	tmp = init_parse_tmp(&i, &j, s, str);
	tmp->len = len;
	while (s[i] &&  j < len && i < start + len) // 만약 key를 value로 바꾼다면 str 동적할당을 value에 맞게 해야한다.
	{
		tmp->type = ft_is_comma(s[i]);
		delete_comma_check_env(token, &keys, tmp);
	}
	str[j] = '\0';
	str = change_key_to_value(str, keys);
	free(tmp);
	if (keys)
		free_keys(keys);
	return (str);
}
