/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_comma_check_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:41:12 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/02 20:12:45 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_keycpy(char *dst, char *src, int dstsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

static t_keys	*ft_keyslast(t_keys *keys)
{
	if (!keys)
		return (NULL);
	while (keys->next)
		keys = keys->next;
	return (keys);
}

static char	*get_env_value_of_key(t_token **token, \
t_keys **keys, char *line, int start)
{
	int		finish;
	char	*key;
	char	*value;

	finish = start;
	if (line[finish] == '$')
	{
		while (line[finish] && line[finish] != ' ' && \
		check_operator_for_env(line[finish]) == NO_TYPE)
			finish++;
		key = malloc(sizeof(char) * (finish - start + 1));
		if (!key)
			throw_error(MALLOC_ERR);
		ft_keycpy(key, &line[start], finish - start + 1);
		(*keys)->key = key;
		value = ft_getenv((*token)->info->env_list, key + 1);
		return (value);
	}
	return (NULL);
}

static void	check_env_record(t_token **token, t_keys **keys, int i)
{
	t_keys	*keys_last;
	int		key_len;

	if (*keys == NULL)
	{
		*keys = ft_calloc(sizeof(t_keys), 1);
		keys_last = (*keys);
	}
	else
	{
		keys_last = ft_keyslast(*keys)->next;
		keys_last = ft_calloc(sizeof(t_keys), 1);
	}
	if (!keys_last)
		throw_error(MALLOC_ERR);
	keys_last->value = get_env_value_of_key(token, \
	&keys_last, (*token)->line, i);
	keys_last->key_len = ft_strlen(keys_last->key);
	keys_last->value_len = ft_strlen(keys_last->value);
}

void	delete_comma_check_env(t_token **token, t_keys **keys, t_parse_tmp *tmp)
{
	int		*i;
	int		*j;
	char	*s;
// 밖에 while문에서 하나씩 캐릭터가 들어온다. 그래서 delete_comma_check_env는 따옴표가 오면=
// 쭉 복사를해주거나 env가 있다면 체크를 해주는 역할을 한다.
	i = tmp->i; // line의 어디부터 읽어야할지 적혀있다.
	j = tmp->j; // cmd의 인덱스를 표현. 여기서는 tmp->str 전용 인덱스이다.
	s = tmp->s; // token의 line이다.
	tmp->type = ft_is_comma(s[(*i)]); 
	if (tmp->type) // 복사를 하는 와중에 따옴표를 발견을 한다면 복사를 한다.
	{
		(*i)++; // 따옴표로 들어온 거니까 다음 같은 따옴표가 나올때까지 복사를 해준다.
		while (s[(*i)] && ft_is_comma(s[(*i)]) != tmp->type && (*j) < tmp->len) // 따옴표가 들어온 경우이기 때문에 while문으로 같은 따옴표를 만날때까지 쭉 저장을 해준다.
		{
			if (tmp->type == TWO_COM && s[(*i)] == '$')
			{
				check_env_record(token, keys, (*i));
				ft_keyslast(*keys)->start_idx = *j;
			}
			tmp->str[(*j)++] = s[(*i)++];
		}
		if (s[(*i)])
			(*i)++;
	}
	else // 따옴표가 아니라면 한글자씩 복사를 한다.
	{
		if (s[(*i)] == '$')
		{
			check_env_record(token, keys, (*i));
			ft_keyslast(*keys)->start_idx = *j;
		}
		tmp->str[(*j)++] = s[(*i)++];
	}
}
