/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2023/01/03 14:10:01 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tok(t_token *tok)
{
	int	i;

	while (tok)
	{
		i = 0;
		printf("line:%s\n", tok->line);
		if (tok->cmd != NULL)
		{
			while (tok->cmd[i])
			{
				printf("cmd:%s\n", tok->cmd[i]);
				i++;
			}
		}
		tok = tok->next;
	}
}

void	print_tree(t_token *tok)
{
	if (tok == 0)
		return ;
	printf("tok:%s :%d\n", tok->line, tok->type);
	print_tree(tok->left);
	print_tree(tok->right);
}

int	run(char *line, t_info *info)
{
	t_token	*token;

	if (g_errno == 1)
	{
		info->exit_num = 1;
		g_errno = 0;
	}
	token = init_token(line, info);
	if (token->err_flag_syn == 1)
		return (free_lst(token, info));
	if (expansion_wild(token) < 0)
		return (free_lst(token, info));
	token = get_tree(ft_tokenlast(token));
	if (check_tree(token) == 1)
		return (err_msg_syntax_int(info));
	open_redir(token);
	if (g_errno == -2)
	{
		g_errno = 0;
		info->exit_num = 1;
		return (info->exit_num);
	}
	run_shell(token);
	free_tree(token);
	return (info->exit_num);
}

void	loop_set(t_info *info)
{
	char	**tmp;

	tmp = info->path;
	tcsetattr(STDIN_FILENO, TCSANOW, info->term);
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
			eof_exit(info);
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
