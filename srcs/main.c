/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:22:19 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/11 18:34:13 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
		return ;
	else if (signo == SIGTERM)
		printf("exit\n");
	return ;
}

void	initial(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTERM, handler);
}

int	main(int ac, char **av)
{
	char	*line;

	initial();
	while (1)
	{
		line = readline("seekko> ");
		if (line)
		{
			if (strcmp(line, "exit") == 0)
				exit(0);
			add_history(line);
			free(line);
			line = 0;
		}
		else
		{
			printf("exit\n");
			return (0);
		}
	}
	return (0);
}
