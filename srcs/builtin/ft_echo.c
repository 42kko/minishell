/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 20:42:08 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/02 21:34:04 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	n_flag;

	n_flag = 1;
	if (ft_strncmp(cmd[0], "echo", 4) != 0)
		throw_error(COMMAND_NOT);
	i = 1;
	if (ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		n_flag = 0;
		i = 2;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
	}
	if (n_flag)
		printf("\n");
}
