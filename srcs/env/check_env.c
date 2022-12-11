/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:55:10 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/11 18:30:20 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*create_idx_arr(t_keys *keys)
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

static	void	init_value(t_change_tmp	*tmp, t_keys *keys, int **idx)
{
	*idx = create_idx_arr(keys);
	(*tmp).i = 0;
	(*tmp).k = 0;
	(*tmp).ord = 0;
	(*tmp).ch_idx = 0;
}

char	*change_key_to_value(char *cmd, t_keys *keys)
{
	char			*str;
	int				*idx;
	t_change_tmp	tmp;

	str = malloc_changed_str(cmd, keys);
	init_value(&tmp, keys, &idx);
	while (cmd[tmp.k])
	{
		if (cmd[tmp.k] == '$' && keys && tmp.i == idx[tmp.ord] + tmp.ch_idx)
		{
			tmp.j = 0;
			while (keys->value[tmp.j])
				str[tmp.i++] = keys->value[tmp.j++];
			tmp.k += keys->key_len;
			tmp.ch_idx += keys->value_len - keys->key_len;
			keys = keys->next;
			tmp.ord = tmp.ord + 1;
		}
		else
			str[tmp.i++] = cmd[tmp.k++];
	}
	str[tmp.i] = '\0';
	free(idx);
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
