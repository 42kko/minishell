/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:36:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/28 16:41:29 by seokchoi         ###   ########.fr       */
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

char	*get_env_value_of_key(t_token **token,t_keys **keys, char *line, int start) // " 나올 때까지 or oper나올때까지
{
	int		finish;
	char	*key;
	char	*value;

	finish = start;
	if (line[finish] == '$')
	{
		while (line[finish] && line[finish] != ' ' && check_operator(line[finish]) == NO_TYPE) // " 안에있는 환경변수인 경우
			finish++;
		key = malloc(sizeof(char) * (finish - start + 1));
		if (!key)
			throw_error(MALLOC_ERR);
		ft_keycpy(key , &line[start], finish - start + 1); // $ 포함된 key가 들어온다.
		(*keys)->key = key;
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

int	check_env_record(t_token **token, t_keys **keys, int i, int j)
{
	t_keys	*keys_last;
	int		key_len;
	if (*keys == NULL) // " 안에있는 환경변수의 경우에는 oper도 포함시킨다.
	{
		(*keys) = ft_calloc(sizeof(t_keys), 1);
		if (!(*keys))
			throw_error(MALLOC_ERR);
		(*keys)->value = get_env_value_of_key(token, keys, (*token)->line, i);
		if (!(*keys)->value)
		{
			(*keys)->value = ft_strdup("");
			if (!(*keys)->value)
				throw_error(MALLOC_ERR);
		}
		(*keys)->key_len = ft_strlen((*keys)->key);
		(*keys)->value_len = ft_strlen((*keys)->value);
		(*keys)->start_idx = j;
	}
	else
	{
		keys_last = ft_keyslast(*keys);
		keys_last->next = ft_calloc(sizeof(t_keys), 1);
		keys_last->next->value = get_env_value_of_key(token, &(keys_last->next), (*token)->line, i);
		if (!keys_last->next->value)
		{
			keys_last->next->value = ft_strdup("");
			if (!keys_last->next->value)
				throw_error(MALLOC_ERR);
		}
		keys_last->next->key_len = ft_strlen(keys_last->next->key);
		keys_last->next->value_len = ft_strlen(keys_last->next->value);
		keys_last->next->start_idx = j;
	}
	
	return (key_len);
}

int		check_env_malloc_len(char *cmd, t_keys *keys)
{
	int	cmd_len;
	int	keys_len;
	int values_len;
	
	cmd_len = ft_strlen(cmd);
	keys_len = 0;
	values_len = 0;
	while (keys)
	{
		keys_len += ft_strlen(keys->key);
		values_len += ft_strlen(keys->value);
		keys = keys->next;
	}
	return (cmd_len - keys_len + values_len + 1);
}

char	*change_key_to_value(char *cmd, t_keys *keys)
{
	int		i;
	int		k;
	int		j;
	char	*str;
	int		str_len;

	str_len = check_env_malloc_len(cmd, keys);
	str = malloc(sizeof(char) * str_len);
	if (!str)
		throw_error(MALLOC_ERR);
	i = 0;
	k = 0;
	j = 0;
	while (cmd[k])
	{
		if (cmd[k] == '$')
		{
			j = 0;
			if (keys)
			{
				while (keys->value[j])
					str[i++] = keys->value[j++];
				k += keys->key_len;
				keys = keys->next;
			}
		}
		else
			str[i++] = cmd[k++];
	}
	str[i] = '\0';
	free(cmd);
	return (str);
}

void	free_keys(t_keys *keys)
{
	t_keys	*tmp;

	if (!keys)
		return ;
	while (keys)
	{
		tmp = keys->next;
		free(keys->value);
		free(keys->key);
		free(keys);
		keys = tmp;
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
	while (s[i] &&  j < len && i < start + len) // 만약 key를 value로 바꾼다면 str 동적할당을 value에 맞게 해야한다.
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
			if (s[i])
				i++;
		}
		else
		{
			if (s[i] == '$') // " 안에있지 않은 환경변수의 경우에는 oper도 포함시킨다.
				check_env_record(token, &keys, i, j);
			str[j++] = s[i++];
		}
	}
	str[j] = '\0';
	str = change_key_to_value(str, keys);
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
