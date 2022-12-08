/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:32:08 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/24 13:42:27 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_brachek_type	ft_is_comma_brachek(char c)
{
	if (c == '\'')
		return (ONE_COMM);
	if (c == '\"')
		return (TWO_COMM);
	if (c == '(')
		return (O_BRACHEK);
	if (c == ')')
		return (C_BRACHEK);
	return (NO_BRACHEK);
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
	return (NO_BRACHEK);
}
