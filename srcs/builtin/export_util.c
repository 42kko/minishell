/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 04:35:37 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/11 04:45:29 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_str(char *key, char *value, size_t *key_len, size_t *val_len)
{
	char	*str;

	*key_len = ft_strlen(key);
	if (value)
	{
		*val_len = ft_strlen(value);
		str = (char *)malloc(sizeof(char) * (*key_len + *val_len + 4));
	}
	else
	{
		*val_len = 0;
		str = (char *)malloc(sizeof(char) * (*key_len + 4));
	}
	if (!str)
		throw_error(MALLOC_ERR);
	return (str);
}

static char	*link_key_value_export(char *key, char *value, int equal)
{
	size_t	key_len;
	size_t	val_len;
	size_t	i;
	size_t	j;
	char	*str;

	if (!key)
		return (0);
	str = set_str(key, value, &key_len, &val_len);
	i = 0;
	j = 0;
	while (j < key_len)
		str[i++] = key[j++];
	if (equal == 0)
	{
		str[i++] = '=';
		str[i++] = '\"';
	}
	j = 0;
	while (j < val_len)
		str[i++] = value[j++];
	if (equal == 0)
		str[i++] = '\"';
	str[i] = '\0';
	return (str);
}

char	**get_export_arr(t_env_list *env_list)
{
	int			num;
	char		**env;
	int			i;
	t_env_list	*tmp;

	i = 0;
	tmp = env_list;
	num = get_env_num(env_list);
	env = malloc(sizeof(char *) * (num + 1));
	if (!env)
		throw_error(MALLOC_ERR);
	while (i < num && tmp)
	{
		if (ft_strncmp(tmp->key, "~", 2) != 0)
		{
			env[i] = link_key_value_export(tmp->key, tmp->value, tmp->equal);
			if (!env[i])
				throw_error(MALLOC_ERR);
			i++;
		}
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
