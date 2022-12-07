/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_comma_check_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:41:12 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/07 12:48:32 by seokchoi         ###   ########.fr       */
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

static char	*case_env_question(t_keys *keys, char *line, int start)
{
	char	*key;
	char	*state;

	key = malloc(sizeof(char) * 3);
	if (!key)
		throw_error(MALLOC_ERR);
	ft_keycpy(key, &line[start], 3);
	keys->key = key;
	state = ft_itoa(errno); // 임시 방편 밑에 꺼로 바꿔야한다.
	if (!state)
		throw_error(MALLOC_ERR);
	return (state); // string 상태의 그것이 와야한다.
}

static char	*get_env_value_of_key(t_token **token, \
t_keys *keys, char *line, int start)
{
	int		finish;
	char	*key;
	char	*value;

	finish = start;
	if (line[finish] == '$')
	{
		if(line[finish + 1] == '?')
			return (case_env_question(keys, line, finish));
		while (line[finish] && line[finish] != ' ' && \
		check_operator_for_env(line[finish]) == NO_TYPE)
			finish++;
		key = malloc(sizeof(char) * (finish - start + 1));
		if (!key)
			throw_error(MALLOC_ERR);
		ft_keycpy(key, &line[start], finish - start + 1);
		keys->key = key;
		value = ft_getenv((*token)->info->env_list, key + 1);
		return (value);
	}
	return (NULL);
}

static void	check_env_record(t_token **token, t_keys **keys, int i, t_parse_tmp *tmp)
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
	keys_last, (*token)->line, i);
	keys_last->key_len = ft_strlen(keys_last->key);
	keys_last->value_len = ft_strlen(keys_last->value);
	keys_last->start_idx = *tmp->j;
}

void	delete_comma_check_env(t_token **token, t_keys **keys, t_parse_tmp *tmp)
{
	char	*s;

	s = tmp->s; // token의 line이다.
	tmp->type = ft_is_comma(s[(*tmp->i)]); 
	if (tmp->type) // 복사를 하는 와중에 따옴표를 발견을 한다면 복사를 한다.
	{
		(*tmp->i)++; // 따옴표로 들어온 거니까 다음 같은 따옴표가 나올때까지 복사를 해준다.
		while (s[(*tmp->i)] && ft_is_comma(s[(*tmp->i)]) != tmp->type && (*tmp->j) < tmp->len) // 따옴표가 들어온 경우이기 때문에 while문으로 같은 따옴표를 만날때까지 쭉 저장을 해준다.
		{
			if (tmp->type == TWO_COM && s[(*tmp->i)] == '$')
				check_env_record(token, keys, (*tmp->i), tmp);
			tmp->str[(*tmp->j)++] = s[(*tmp->i)++];
		}
		if (s[(*tmp->i)])
			(*tmp->i)++;
	}
	else // 따옴표가 아니라면 한글자씩 복사를 한다.
	{
		if (s[(*tmp->i)] == '$')
			check_env_record(token, keys, (*tmp->i), tmp);
		tmp->str[(*tmp->j)++] = s[(*tmp->i)++];
	}
}
