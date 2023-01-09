/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:18:35 by kko               #+#    #+#             */
/*   Updated: 2022/12/11 21:29:14 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *msg, t_token *tok, char *target)
{
	(void)msg;
	(void)tok;
	ft_putstr_fd("minishell: ", 2);
	if (target != 0)
	{
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	throw_error_syntax(t_error_type type, t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	if (tmp == 0)
		return ;
	if (type == SYNTAX_ERR)
	{
		while (tmp->prev)
			tmp = tmp->prev;
		tmp->err_flag_syn = 1;
	}
	else
		tmp->err_flag_syn = 1;
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

static void	error_message_exit(char *message, t_error_type type)
{
	ft_putstr_fd(message, 2);
	exit(type);
}

void	throw_error(t_error_type type)
{
	if (type == MALLOC_ERR)
		error_message_exit("ERROR : MALLOR_ERR", type);
	if (type == SYNTAX_ERR)
		error_message_exit("syntax error near unexpected token\n", type);
}
