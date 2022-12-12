/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_env_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:18:54 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 20:28:28 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_put_wave(t_env_list **env_list, char *key)
{
	char		*value;

	if (ft_strncmp(key, "~", 2) == 0)
	{
		value = ft_getenv(*env_list, key);
		throw_error_message("unset", value, "not a valid identifier", 1);
		free(value);
		return (1);
	}
	else
		return (0);
}

void	ft_unset_env_list(t_env_list **env_list, char *key)
{
	t_env_list	*tmp_a;
	t_env_list	*tmp_b;

	tmp_a = *env_list;
	tmp_b = tmp_a;
	if (if_put_wave(env_list, key))
		return ;
	while (tmp_a)
	{
		if (!ft_strncmp(key, tmp_a->key, ft_strlen(key) + 1))
		{
			if (tmp_a == *env_list)
			{
				*env_list = tmp_a->next;
				free_a_node_of_env_list(tmp_a);
				return ;
			}
			tmp_b->next = free_a_node_of_env_list(tmp_a);
			return ;
		}
		tmp_b = tmp_a;
		tmp_a = tmp_a->next;
	}
}
