/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:08:30 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/08 18:18:30 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_message_exit(char *message, t_error_type type)
{
	ft_putstr_fd(message, 2);
	exit(type);
}

void	throw_error(t_error_type type)
{
	if (type == MALLOC_ERR)
		error_message_exit("ERROR : MALLOR_ERR", type);
	if (type == SYNTAX_ERR) //만들었던 토큰화를 전부 할당해제해준다.
		error_message_exit("syntax error near unexpected token\n", type);
	if (type == FORK_ERR)
		error_message_exit("ERROR : FORK_ERR", type);
	if (type == COMMAND_NOT)
		error_message_exit("comman not found", type);
	// error_message_exit("syntax error near unexpected token", type);
}

void	throw_error_message(char *cmd, char *err, char *message, int exit_errno)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (err != NULL)
	{
		ft_putstr_fd(err, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	errno = exit_errno;
}
