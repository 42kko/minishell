/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:55:10 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/29 21:17:52 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_key_to_value(char *cmd, t_keys *keys)
{
	int		i;
	int		k;
	int		j;
	char	*str;

	str = malloc_changed_str(cmd, keys);
	i = 0;
	k = 0;
	while (cmd[k])
	{
		if (cmd[k] == '$' && keys)
		{
			j = 0;
			while (keys->value[j])
				str[i++] = keys->value[j++];
			k += keys->key_len;
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