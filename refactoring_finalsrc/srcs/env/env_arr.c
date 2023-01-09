/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:21:03 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/08 11:51:07 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_num(t_env_list *env_list)
{
	int	num;

	num = 0;
	while (env_list)
	{
		num++;
		env_list = env_list->next;
	}
	return (num);
}

static char	*link_key_value(char *key, char *value, int equal)
{
	size_t	key_len;
	size_t	val_len;
	size_t	i;
	size_t	j;
	char	*str;

	if (!key || !value)
		return (0);
	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	str = (char *)malloc(sizeof(char) * (key_len + val_len + 2));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (j < key_len)
		str[i++] = key[j++];
	if (equal == 0)
		str[i++] = '=';
	j = 0;
	while (j < val_len)
		str[i++] = value[j++];
	str[i] = '\0';
	return (str);
}

char	**get_env_arr(t_env_list *env_list)
{
	int			num;
	char		**env;
	int			i;
	t_env_list	*tmp;

	i = 0;
	tmp = env_list;
	num = get_env_num(env_list);
	env = ft_calloc(sizeof(char *), (num + 1));
	if (!env)
		throw_error(MALLOC_ERR);
	while (i < num && tmp)
	{
		if (tmp->equal == 0 && ft_strncmp(tmp->key, "~", 2) != 0)
		{
			env[i] = link_key_value(tmp->key, tmp->value, tmp->equal);
			if (!env[i])
				throw_error(MALLOC_ERR);
			i++;
		}
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
