/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:15 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/08 00:13:24 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_token *token)
{
	t_env_list	*env_list;
	int			cmd_len;

	cmd_len = get_sec_arr_len(token->cmd);
	env_list = token->info->env_list;
	if (cmd_len == 1)
	{
		
	}
	if (token->cmd[1])
	{
		ft_putenv(env_list, token->cmd[1])
	}
}