/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:51:52 by kko               #+#    #+#             */
/*   Updated: 2022/12/05 21:45:42 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>


// void	loop(char **envp)
// {
// 	char	*line;
// 	t_info	*info;
// 	pid_t	execute_pid;
// 	t_token	*tok;

// 	info = malloc(sizeof(t_info));
// 	if (!info)
// 		throw_error(MALLOC_ERR);
// 	init_env(info, envp);
// 	while (1)
// 	{
// 		line = readline("seekko> ");
// 		if (line && line[0] != '\0')
// 		{
// 			if (strcmp(line, "exit") == 0) // 고치기
// 			{
// 				free(line);
// 				return ;
// 			}
// 			add_history(line);
// 			execute_pid = fork();
// 			if (execute_pid == -1)
// 				throw_error(FORK_ERR);
// 			if (execute_pid == 0)
// 			{
// 				tok = init_token(line, info);
// 				run(tok);
// 				exit(0);
// 				// 잘끝나면 token 동적할당 됐을 거고
// 				// 아니면 exit로 에러를 내보냄
// 			}
// 			waitpid(execute_pid, NULL, 0);
// 			free(line);
// 			line = 0;
// 			// run(tok);
// 			// free_tree(tok);
// 		}
// 		else if(line == 0)
// 		{
// 			free(line);
// 			line = 0;
// 			return ;
// 		}
// 		else
// 		{
// 			free(line);
// 			line = 0;
// 		}
// 	}
// }

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

void	free_tree(t_token *tok)
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

int	run(char *line, t_info *info)
{
	t_token	*token;

	token = init_token(line, info);
	if (token->err_flag_syn == 1)
		return (free_lst(token));
	token = get_tree(ft_tokenlast(token));
	if (check_tree(token) == 1)
		return (1);
	// printf("succ\n");
	run_shell(token);
	return (0);
}

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
	printf("start errno:%d\n", errno);
	while (1)
	{
		line = readline("seekko> ");
		if (line == NULL)
		{
			printf("ctrl+d\n");
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
