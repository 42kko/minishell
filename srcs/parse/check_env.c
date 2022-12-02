/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:55:10 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/02 03:31:56 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		*create_idx_arr(t_keys *keys)
{
	int		len;
	int		*idx;
	t_keys	*tmp;
	int		i;

	i = 0;
	len = 0;
	tmp = keys;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	idx = malloc(sizeof(int) * len);
	if (!idx)
		throw_error(MALLOC_ERR);
	while (keys && i < len)
	{
		idx[i] = keys->start_idx;
		keys = keys->next;
		i++;
	}
	return (idx);
}

char	*change_key_to_value(char *cmd, t_keys *keys)
{
	int		i;
	int		k;
	int		j;
	char	*str;
	int		ord;
	int		*idx;
	int		changed_idx;

	str = malloc_changed_str(cmd, keys);
	idx = create_idx_arr(keys);
	i = 0;
	k = 0;
	ord = 0;
	changed_idx = 0;
	while (cmd[k])
	{
		if (cmd[k] == '$' && keys && k == idx[ord] + changed_idx)
		{
			j = 0;
			while (keys->value[j])
				str[i++] = keys->value[j++];
			k += keys->key_len;
			changed_idx = keys->value_len - keys->key_len;
			keys = keys->next;
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