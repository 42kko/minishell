/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_syntax_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 01:38:23 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/02 09:46:13 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg_syntax_int(t_info *info)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	info->exit_num = 258;
	return (258);
}
