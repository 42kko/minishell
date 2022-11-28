/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/11/28 11:54:42 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>


void	loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("seekko> ");
		if (line)
		{
			if (strcmp(line, "exit") == 0)
			{
				free(line);
				return ;
			}
			add_history(line);
			init_token(line);
			free(line);
			line = 0;
		}
		else
		{
			free(line);
			line = 0;
			printf("exit\n");
			return ;
		}
	}
}