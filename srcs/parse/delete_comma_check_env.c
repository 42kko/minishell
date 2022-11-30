/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_comma_check_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:41:12 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/30 17:04:33 by seokchoi         ###   ########.fr       */
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
		check_operator(line[finish]) == NO_TYPE)
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

void	delete_comma_check_env(t_token **token, t_keys **keys,t_parse_tmp *tmp)
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
			tmp->str[(*j)++] = s[(*i)++];
		if (s[(*i)])
			(*i)++;
	}
	else
	{
		if (s[(*i)] == '$')
			check_env_record(token, keys, (*i));
		tmp->str[(*j)++] = s[(*i)++];
	}
}
