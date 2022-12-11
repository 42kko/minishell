/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:26 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/11 04:26:39 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_token *token)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	key = NULL;
	value = NULL;
	while (token->cmd[i])
	{	
		ft_split_for_env(token->cmd[i], &key, &value);
		ft_unset_env_list(&token->info->env_list, key);
		if (is_dont_be_key(key) == FAIL)
		{
			token->info->exit_num = 1;
			throw_error_message("unset", token->cmd[i], \
			"not a valid identifier", 1);
		}
		key = NULL;
		value = NULL;
		i++;
	}
}
