/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/11/26 16:17:26 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>


void	loop(char **envp)
{
	char	*line;
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		throw_error(MALLOC_ERR);
	init_env(info, envp);
	while (1)
	{
		line = readline("seekko> ");
		if (line)
		{
			if (strcmp(line, "exit") == 0)
				return ;
			add_history(line);
			init_token(line, info);
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