/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/11/28 19:53:24 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>


void	loop(void)
{
	char	*line;
	t_token	*tok;

	while (1)
	{
		line = readline("seekko> ");
		if (line && line[0] != '\0')
		{
			if (strcmp(line, "exit") == 0)
			{
				free(line);
				return ;
			}
			add_history(line);
			tok = init_token(line);
			free(line);
			line = 0;
			run(tok);
			// free_tree(tok);
		}
		else if(line == 0)
		{
			free(line);
			line = 0;
			return ;
		}
		else
		{
			free(line);
			line = 0;
		}
	}
}