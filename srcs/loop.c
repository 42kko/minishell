/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/11/30 21:10:46 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>


void	loop(char **envp)
{
	char	*line;
	t_info	*info;
	pid_t	execute_pid;
	t_token	*tok;

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
				tok = init_token(line, info);
				run(tok);
				exit(0);
				// 잘끝나면 token 동적할당 됐을 거고
				// 아니면 exit로 에러를 내보냄
			}
			waitpid(execute_pid, NULL, 0);
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
