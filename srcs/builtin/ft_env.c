/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:43 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/11 16:20:41 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_token *token)
{
	t_env_list	*env_list;

	env_list = token->info->env_list;
	if (get_sec_arr_len(token->cmd) > 1)
	{
		token->info->exit_num = 1;
		throw_error_message("exit", NULL, "too many arguments", 1);
		return ;
	}
	print_envs(token->info->env_list);
}
