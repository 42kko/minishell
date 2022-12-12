/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:31:59 by kko               #+#    #+#             */
/*   Updated: 2022/12/12 20:32:26 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_export_util(t_token *token, int *flag, char **key, char **value)
{
	if (*flag == SUCCESS)
		ft_putenv(token->info->env_list, *key, *value, 0);
	else if (*flag == 2)
		ft_putenv(token->info->env_list, *key, *value, 1);
	token->info->exit_num = 0;
}
