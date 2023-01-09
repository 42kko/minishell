/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:31:59 by kko               #+#    #+#             */
/*   Updated: 2023/01/08 10:07:38 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_value(t_env_list *env_list, char *key)
{
	t_env_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
		{
			if (tmp->equal == 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	check_export_util(t_token *token, int *flag, char **key, char **value)
{
	int	fail_flag;

	fail_flag = 0;
	if (*flag == SUCCESS)
	{
		ft_putenv(token->info->env_list, *key, *value, 0);
		if (ft_strncmp(*key, "HOME", 5) == 0)
			ft_putenv(token->info->env_list, "~", *value, 0);
	}
	else if (*flag == 2)
	{
		if (!has_value(token->info->env_list, *key))
		{
			token->info->exit_num = 0;
			return ;
		}
		ft_putenv(token->info->env_list, *key, *value, 1);
	}
	token->info->exit_num = 0;
}
