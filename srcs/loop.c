/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/12/09 10:01:10 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run(char *line, t_info *info)
{
	t_token	*token;

	token = init_token(line, info);
	if (token->err_flag_syn == 1)
		return (free_lst(token));
	// free_lst(token);
	token = get_tree(ft_tokenlast(token));
	if (check_tree(token) == 1)
		return (1);
	open_redir(token);
	if (errno == -1)
		return (1);
	run_shell(token);
	free_tree(token);
	return (0);
}

void	eof_exit(char *line, t_info *info)
{
	printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, info->old_term);
	exit(0);
}

void	loop(t_info *info)
{
	char	*line;

	while (1)
	{
		line = readline("seekko> ");
		if (line == NULL)
			eof_exit(line, info);
		else if (line != NULL && *line != '\0')
		{
			add_history(line);
		}
		else
		{
			free(line);
			line = NULL;
			continue ;
		}
		run(line, info);
		// exit(0);
	}
}
