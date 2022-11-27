/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:36:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/27 18:23:38 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pull_until_same_comma(char *str, int *i, t_comma_type flag)
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
		while (ft_is_comma(line[*index]) == NO_COM && line[*index] != ' ' && line[*index] != '\0' && ft_is_redir(line[*index]) == NO_TYPE)
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
	// while ()
	// {
		
	// }
	i += s1_len;
	return (changed);
}


int	ft_keycpy(char *dst, char *src, int dstsize)
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


char	*get_env_key(t_token **token, char *line, int start) // " 나올 때까지 or oper나올때까지
{
	int		finish;
	char	*key;
	char	*value;

	finish = start;
	if (line[finish] == '$')
	{
		finish++;
		while (line[finish] && line[finish] != ' ' && check_operator(line[finish]) != NO_TYPE) // " 안에있는 환경변수인 경우
			finish++;
		key = malloc(sizeof(char) * (finish - start + 1));
		if (!key)
			throw_error(MALLOC_ERR);
		ft_keycpy(key , &line[start], finish - start); // $ 포함된 key가 들어온다.
		key[finish - start] = '\0';
		value = ft_getenv((*token)->info->env_list, key + 1);
		return (value);
	}
	return (NULL);
}

t_keys *ft_keyslast(t_keys *keys)
{
	if (!keys)
		return (NULL);
	while (keys->next)
		keys = keys->next;
	return (keys);
}

void	check_env_record(t_token **token, t_keys **keys, int i, int j)
{
	t_keys	*keys_last;

	if (*keys == NULL) // " 안에있는 환경변수의 경우에는 oper도 포함시킨다.
	{
		(*keys) = ft_calloc(sizeof(t_keys), 1);
		if (!(*keys))
			throw_error(MALLOC_ERR);
		(*keys)->key = get_env_key(token, (*token)->line, i);
		(*keys)->start_idx = j;
	}
	else
	{
		keys_last = ft_keyslast(*keys);
		keys_last->next = ft_calloc(sizeof(t_keys), 1);
		keys_last->next->key = get_env_key(token, (*token)->line, i);;
		keys_last->next->start_idx = j;
	}
}

char	*ft_strdup_without_check_comma(t_token **token, char *s, int start, int len) // " 안에 있는 환경변수를 바꿔줄 수  있있어야한다.
{
	char			*str;
	int				i;
	int				j;
	t_comma_type	type;
	t_keys			*keys;
	t_keys			*keys_last;

	i = start;
	j = 0;
	keys = NULL;
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
				if (type == TWO_COM && s[i] == '$') // comma 타입중에서 " 일때만 환경변수 처리
					check_env_record(token, &keys, i, j);
				str[j++] = s[i++];
			}
			// if (ft_is_comma(s[i]) != type) // 꼬님이 토큰 쪽에서 이미 처리했다고 함.
			// 	throw_error(SYNTAX_ERR);
			if (s[i])
				i++;
		}
		else
		{
			// $가 들어올 경우
			if (s[i] == '$') // " 안에있지 않은 환경변수의 경우에는 oper도 포함시킨다.
			{
				printf("여기가 돌았겠네\n");
				check_env_record(token, &keys, i, j);
			}
			str[j++] = s[i++];
		}
	}
	str[j] = '\0';
	t_keys			*keys_tmp;
 
	keys_tmp = keys; 
	while (keys_tmp) // key 확인
	{
		printf("key = %s\n", keys_tmp->key);
		keys_tmp = keys_tmp->next;
	}
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
