/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:36:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 00:35:47 by kko              ###   ########.fr       */
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

char	*cpy_wout_com(t_token **token, char *s, int start, int len)
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
	while (s[i] && j < len && i < start + len)
		delete_comma_check_env(token, &keys, tmp);
	str[j] = '\0';
	str = change_key_to_value(str, keys);
	free(tmp);
	if (keys)
		free_keys(keys);
	return (str);
}
