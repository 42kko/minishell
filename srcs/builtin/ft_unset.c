/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:26 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/08 16:14:46 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_token *token)
{
	
	if (token->cmd[1])
	{
		// ft_unset_env_list(token->info->env_list, cm)
		errno = 0;
	}
	else
		return ;
}