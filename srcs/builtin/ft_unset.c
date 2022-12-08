/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:26 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 00:54:27 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_token *token)
{
	char	*key;
	char	*value;

	if (token->cmd[1])
	{
		ft_split_for_env(token->cmd[1], &key, &value);
		ft_unset_env_list(&token->info->env_list, key);
		errno = 0;
	}
	else
	{
		throw_error_message("unset", NULL, "not enough arguments", 1);
		return ;
	}
}
