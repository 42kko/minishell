/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/11/30 17:46:17 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>


void	loop(char **envp)
{
	char	*line;
	t_info	*info;
	pid_t	execute_pid;

	info = malloc(sizeof(t_info));
	if (!info)
		throw_error(MALLOC_ERR);
	init_env(info, envp);
	while (1)
	{
		line = readline("seekko> ");
		if (line && line[0] != '\0')
		{
			if (strcmp(line, "exit") == 0) // 고치기
			{
				free(line);
				return ;
			}
			add_history(line);
			execute_pid = fork();
			if (execute_pid == -1)
				throw_error(FORK_ERR);
			if (execute_pid == 0)
			{
				init_token(line, info);
			}
			waitpid(execute_pid, );
			free(line);
			line = 0;
			// run(tok);
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
