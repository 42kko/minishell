/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:20:58 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 19:49:08 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	can_be_exit_num(char *num)
{
	int	i;
	int	flag;

	flag = SUCCESS;
	i = 0;
	if (!num)
		return (FAIL);
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			flag = FAIL;
		i++;
	}
	return (flag);
}

void	ft_exit(t_token *tok, char **cmd)
{
	if (cmd[1] == NULL)
	{
		printf("exit\n");
		exit(tok->info->exit_num);
	}
	else if (can_be_exit_num(cmd[1]) == 1)
	{
		if (cmd[2] != 0)
		{
			tok->info->exit_num = 1;
			throw_error_message("exit", NULL, "too many arguments", 1);
		}
		else
		{
			printf("exit\n");
			exit(ft_atoi(cmd[1]));
		}
	}
	else
	{
		printf("exit\n");
		throw_error_message("exit", cmd[1], "numeric argument required", 255);
		exit(255);
	}
}
