/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_comma_check_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:41:12 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/11 21:23:03 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*case_env_question(t_token **token, \
t_keys *keys, char *line, int start)
{
	char	*key;
	char	*state;

	key = malloc(sizeof(char) * 3);
	if (!key)
		throw_error(MALLOC_ERR);
	ft_keycpy(key, &line[start], 3);
	keys->key = key;
	state = ft_itoa((*token)->info->exit_num);
	if (!state)
		throw_error(MALLOC_ERR);
	return (state);
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
		if (line[finish + 1] == '?')
			return (case_env_question(token, keys, line, finish));
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

static void	check_env_record(t_token **token, \
t_keys **keys, int i, t_parse_tmp *tmp)
{
	t_keys	*keys_last;

	if (*keys == NULL)
	{
		*keys = ft_calloc(sizeof(t_keys), 1);
		keys_last = (*keys);
	}
	else
	{
		keys_last = ft_keyslast(*keys);
		keys_last->next = ft_calloc(sizeof(t_keys), 1);
		keys_last = keys_last->next;
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

	s = tmp->s;
	tmp->type = ft_is_comma(s[(*tmp->i)]);
	if (tmp->type)
	{
		(*tmp->i)++;
		while (s[(*tmp->i)] && ft_is_comma(s[(*tmp->i)]) != \
		tmp->type && (*tmp->j) < tmp->len)
		{
			if (tmp->type == TWO_COM && s[(*tmp->i)] == '$')
				check_env_record(token, keys, (*tmp->i), tmp);
			tmp->str[(*tmp->j)++] = s[(*tmp->i)++];
		}
		if (s[(*tmp->i)])
			(*tmp->i)++;
	}
	else
	{
		if (s[(*tmp->i)] == '$')
			check_env_record(token, keys, (*tmp->i), tmp);
		tmp->str[(*tmp->j)++] = s[(*tmp->i)++];
	}
}
