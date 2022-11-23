/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:32:08 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/23 16:34:22 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_comma_type    ft_is_comma_brachek(char c) // 괄호도 찾을 수 있게 수정했습니다.
{
    if (c == '\'')
        return (ONE_COM);
    if (c == '\"')
        return (TWO_COM);
    if (c == '(')
        return (O_BRACHEK);
    if (c == ')')
        return (C_BRACHEK);
    return (NO_COM);
}

t_comma_type	ft_is_comma(char c)
{
	if (c == '\'')
		return (ONE_COM);
	if (c == '\"')
		return (TWO_COM);
	return (NO_COM);
}

t_redir_type	ft_is_redir(char c)
{
	if (c == '<')
		return (O_DIREC);
	if (c == '>')
		return (C_DIREC);
	return (NO_DIREC);
}

t_brachek_type	ft_is_brachek(char c)
{
	if (c == '\'')
		return (O_BRACHEK);
	if (c == '\"')
		return (C_BRACHEK);
	return (NO_COM);
}
