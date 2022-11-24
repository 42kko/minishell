/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:08:30 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/25 00:45:21 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	error_message_exit(char *message, t_error_type type)
{
	ft_putstr_fd(message, 2);
	exit(type);
}

void	throw_error(t_error_type type)
{
	if (type == MALLOC_ERR)
		error_message_exit("ERROR : MALLOR_ERR", type);
	if (type == PARSE_ERR)
		error_message_exit("ERROR : PARSE_ERR", type);
	if (type == SYNTAX_ERR)
	{
		ft_putstr_fd("syntax error near unexpected token", 2);
		// exit(1);
	}
	// error_message_exit("syntax error near unexpected token", type);
}
