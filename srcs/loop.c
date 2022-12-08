/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/12/08 17:48:01 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (cmd == 0)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = 0;
		i++;
	}
	free(cmd);
	cmd = 0;
}

int	free_lst(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tok)
	{
		tmp = tok;
		free_cmd(tok->cmd);
		free(tok->line);
		tok->line = 0;
		tok = tok->next;
		free(tmp);
	}
	printf("syntax error\n");
	return (1);
}

static void	free_tree(t_token *tok)
{
	if (tok == NULL)
		return ;
	free_tree(tok->left);
	free_tree(tok->right);
	free_cmd(tok->cmd);
	if (tok->line != NULL)
	{
		free(tok->line);
		tok->line = 0;
	}
	free(tok);
	tok = 0;
	return ;
}

void	viewtree2(t_token *tok)
{
	t_token	*tmp;

	if (tok == 0)
		return ;
	if (tok->err_flag_syn == 1)
	{
		tmp = tok;
		while (tmp->parent)
			tmp = tmp->parent;
		tmp->err_flag_syn = 1;
	}
	viewtree2(tok->left);
	viewtree2(tok->right);
}

int	check_tree(t_token *token)
{
	viewtree(token);
	viewtree2(token);
	if (token->err_flag_syn == 1)
	{
		free_tree(token);
		return (1);
	}
	return (0);
}

void	check_cmd_num(t_token *token, int *cmd_num)
{
	if (token->type == TCMD)
		(*cmd_num)++;
	if (token->left)
		check_cmd_num(token->left, cmd_num);
	if (token->right)
		check_cmd_num(token->right, cmd_num);
}

int	run(char *line, t_info *info)
{
	t_token	*token;
	int		cmd_num;

	cmd_num = 0;
	token = init_token(line, info);
	if (token->err_flag_syn == 1)
		return (free_lst(token));
	// ft_tokeniter(token);
	token = get_tree(ft_tokenlast(token));
	if (check_tree(token) == 1)
		return (1);
	open_redir(token); // 먼저 모든 리디렉토리를 열어주고 시작한다. 각 fd_in, fd_out에 저장되어있다.
	check_cmd_num(token, &cmd_num);
	if (errno == -1)
		return (1);
	if (cmd_num == 1 && identify_built_exec(token->right) == 1)
		builtin_alone_exec(token);
	else
		run_shell(token);
	return (0);
}

void	loop(t_info *info)
{
	char	*line;

	while (1)
	{
		line = readline("seekko> ");
		if (line == NULL) // line 널이면 readline이 오류를 뱉은 건가...
		{
			printf("ctrl+d\n");
			tcsetattr(STDIN_FILENO, TCSANOW, info->old_term);
			exit(1);
		}
		else if (line != NULL && *line != '\0')
			add_history(line);
		else
		{
			free(line);
			line = NULL;
			continue ;
		}
		run(line, info);
		free(line);
		line = NULL;
	}
}
