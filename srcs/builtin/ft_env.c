/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:43 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 20:22:16 by kko              ###   ########.fr       */
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
	token->info->exit_num = 0;
	print_envs(token->info->env_list);
}
