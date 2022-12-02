/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:36:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/02 20:13:59 by seokchoi         ###   ########.fr       */
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

char	*cpy_wout_com(t_token **token, char *s, int start, int len) // " 안에 있는 환경변수를 바꿔줄 수  있있어야한다. 끊을 cmd의 일부분을 길이를 넘겨줘서 끊을 것이다.
{
	char			*str;
	int				i;
	int				j;
	t_keys			*keys;
	t_parse_tmp		*tmp;
// 주어진 길이와 start부터 len의 길이만큼 자르는데 그안에서 따옴표는 없애줘야하고 env가 있다면 체크를 해서 따로 저장을 해줘야한다.
	i = start; // s=line의 어디부터 읽어야할지 기록되어있다.
	j = 0;  // 명령어 부분을 기록할 인덱스이다.
	keys = NULL;
	str = malloc_str(len); //  1. "$HOME" 2. <sfesdf 3. 'seifj$osdjfe'"$LOGNAME" 이놈들의 저장할 동적할당. 
	tmp = init_parse_tmp(&i, &j, s, str);
	tmp->len = len; // 끊을 길이가 들어온다.
	while (s[i] &&  j < len && i < start + len) // 만약 key를 value로 바꾼다면 str 동적할당을 value에 맞게 해야한다.
	{ // 한 캐릭터씩 저장을 할건데 콤마가 나올경우를 체크하는 것이다
		delete_comma_check_env(token, &keys, tmp); // 길이가 주어지고 그 안에서 따옴표를 제외하고 환경변수를 체크하는 함수
	}
	str[j] = '\0';
	str = change_key_to_value(str, keys);
	free(tmp);
	if (keys)
		free_keys(keys);
	return (str);
}
