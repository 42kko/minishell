/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:55:10 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/28 21:43:01 by seokchoi         ###   ########.fr       */
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

static char	*get_env_value_of_key(t_token **token,t_keys **keys, char *line, int start) // " 나올 때까지 or oper나올때까지
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

static t_keys *ft_keyslast(t_keys *keys)
{
	if (!keys)
		return (NULL);
	while (keys->next)
		keys = keys->next;
	return (keys);
}

int	check_env_record(t_token **token, t_keys **keys, int i)
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
	}
	else
	{
		keys_last = ft_keyslast(*keys);
		keys_last->next = ft_calloc(sizeof(t_keys), 1);
		keys_last->next->value = get_env_value_of_key(token, &(keys_last->next), (*token)->line, i);
		keys_last->next->key_len = ft_strlen(keys_last->next->key);
		keys_last->next->value_len = ft_strlen(keys_last->next->value);
	}
	return (key_len);
}

static int		check_env_malloc_len(char *cmd, t_keys *keys)
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

	printf_key(keys);
	while (keys)
	{
		tmp = keys->next;
		free(keys->value);
		free(keys->key);
		free(keys);
		keys = tmp;
	}
}

// echo $HOME<sddfei asldij elwj cat >dsd $dfaije $HOME