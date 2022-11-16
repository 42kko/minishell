/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/11/16 21:55:14 by kko              ###   ########.fr       */
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
				return ;
			add_history(line);
			create_token(line);
			// free(line);
			line = 0;
		}
		else
		{
			printf("exit\n");
			return ;
		}
	}
}