/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/11/22 20:57:48 by seokchoi         ###   ########.fr       */
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
			init_token(line);
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