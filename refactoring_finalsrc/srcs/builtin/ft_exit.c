/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:21:00 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/08 10:07:11 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *num)
{
	int	i;

	i = 0;
	if (!num)
		return (0);
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit_with_print(t_token *tok, char **cmd, \
int number, int err_code)
{
	printf("exit\n");
	if (err_code == 1)
		throw_error_message("exit", cmd[1], "numeric argument required", 255);
	tcsetattr(STDIN_FILENO, TCSANOW, tok->info->old_term);
	exit(number);
}

void	ft_exit(t_token *tok, char **cmd)
{
	if (cmd[1] == NULL)
		ft_exit_with_print(tok, cmd, tok->info->exit_num, 0);
	else if (is_num(cmd[1]))
	{
		if (cmd[2] != 0)
		{
			tok->info->exit_num = 1;
			printf("exit\n");
			throw_error_message("exit", NULL, "too many argument", 1);
		}
		else
			ft_exit_with_print(tok, cmd, ft_atoi(cmd[1]), 0);
	}
	else
		ft_exit_with_print(tok, cmd, 255, 1);
}
