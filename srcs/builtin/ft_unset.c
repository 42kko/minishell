/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:26 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 20:30:29 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	key_value_free(char **key, char **value)
{
	if (*key)
		free(*key);
	if (*value)
		free(*value);
	*key = NULL;
	*value = NULL;
}

void	ft_unset(t_token *token)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	key = NULL;
	value = NULL;
	token->info->exit_num = 0;
	while (token->cmd[i])
	{	
		ft_split_for_env(token->cmd[i], &key, &value);
		if (is_dont_be_key(key) == FAIL)
		{
			token->info->exit_num = 1;
			throw_error_message("unset", token->cmd[i], \
			"not a valid identifier", 1);
		}
		else
		{
			ft_unset_env_list(&token->info->env_list, key);
		}
		key_value_free(&key, &value);
		i++;
	}
}
