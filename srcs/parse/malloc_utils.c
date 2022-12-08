/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:46:46 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 02:30:33 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_env_malloc_len(char *cmd, t_keys *keys)
{
	int	cmd_len;
	int	keys_len;
	int	values_len;

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

char	*malloc_str(int len)
{
	char	*str;

	str = malloc(sizeof(char) * len + 1);
	if (!str)
		throw_error(MALLOC_ERR);
	return (str);
}

char	*malloc_changed_str(char *cmd, t_keys *keys)
{
	char	*str;
	int		str_len;

	str_len = check_env_malloc_len(cmd, keys);
	str = malloc(sizeof(char) * str_len);
	if (!str)
		throw_error(MALLOC_ERR);
	return (str);
}
