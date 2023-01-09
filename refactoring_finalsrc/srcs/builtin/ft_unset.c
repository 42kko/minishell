/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:14:33 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/08 12:32:03 by jihonkim         ###   ########.fr       */
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
	token->info->exit_num = 0;
	key = NULL;
	value = NULL;
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
			ft_unset_env_list(&token->info->env_list, key);
		i++;
		key_value_free(&key, &value);
	}
}
