/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:03:34 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/08 10:12:27 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd, t_token *token)
{
	int	i;
	int	newline_flag;

	i = 1;
	newline_flag = 1;
	while (cmd[i] && ft_strncmp(cmd[i], "-n", 3) == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
		{
			printf(" ");
		}
	}
	if (newline_flag == 1)
		printf("\n");
	token->info->exit_num = 0;
}
