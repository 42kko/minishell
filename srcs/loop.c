/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/12/10 13:51:42 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run(char *line, t_info *info)
{
	t_token	*token;
	char	*err_cmd;

	token = init_token(line, info);
	if (token->err_flag_syn == 1)
		return (free_lst(token, info));
	if (expansion_wild(token) < 0)
		return (free_lst(token, info));
	token = get_tree(ft_tokenlast(token));
	if (check_tree(token) == 1)
		return (err_msg_syntax_int(info));
	open_redir(token);
	run_shell(token);
	free_tree(token);
	return (info->exit_num);
}

void	eof_exit(char *line, t_info *info)
{
	printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, info->old_term);
	exit(0);
}

void	loop_set(t_info *info)
{
	char	**tmp;

	tmp = info->path;
	dup2(info->stdio_backup[0], 0);
	dup2(info->stdio_backup[1], 1);
	info->path = info_get_path(info);
	free_cmd(tmp);
	errno = 0;
}

void	loop(t_info *info)
{
	char	*line;

	while (1)
	{
		loop_set(info);
		line = readline("minishell$ ");
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
	}
}
