/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:57:22 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/05 19:24:29 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_or_num(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == TDAND || token->type == TOR)
			count++;
		token = token->next;
	}
	return (count);
}

t_token	*get_start_cmd_part(t_token **token)
{
	t_token	*start;

	start = (*token);
	while ((*token) && (*token)->type != TDAND && (*token)->type != TOR)
		(*token) = (*token)->next;
	return (start);
}

t_token **split_cmd_part(t_token *token, int num_and_or)
{
	t_token **cmd_part;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	cmd_part = malloc(sizeof(t_token *) * num_and_or + 1);
	while (i < num_and_or && tmp)
	{
		cmd_part[i] = get_start_cmd_part(&tmp);
		if (tmp)
			tmp = tmp->next;
		i++;
	}
	cmd_part[i] = NULL;
	return (cmd_part);
}

// void	e
// {
	
// }


void	print_cmd_part(t_token **cmd_part)
{
	int	i;
	t_token	*tmp;

	i = 0;
	while (cmd_part[i])
	{
		tmp = cmd_part[i];
		printf("cmd_part %d\n", i + 1);
		while (tmp && tmp->type != NO_TYPE && tmp->type != TDAND && tmp->type != TOR)
		{
			printf("line = %s\n", tmp->line);
			tmp = tmp->next;
		}
		printf("-------------\n");
		if (tmp && tmp->type == NO_TYPE && tmp->type == TDAND && tmp->type == TOR)
		{	
			if (tmp->type == NO_TYPE)
				printf("line = NO_TYPE \n");
			if (tmp->type == TDAND)
				printf("line = TDAND \n");
			if (tmp->type == TOR)
				printf("line = TOR \n");
		}
		else if (tmp == NULL)
			printf("NULL\n");
		printf("-------------\n");
		i++;
	}
}

void	free_list(t_token	*token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		free_sec_arr(tmp->cmd);
		tmp = tmp->next;
	}
}

void	exec(char *line, t_info *info)
{
	t_token	*token;
	t_token **cmd_part;
	int		num_and_or;

	token = init_token(line, info);
	if (token->err_flag_syn == 1)
		return (free_lst(token));
	num_and_or = check_dand_dor_num(token);
	cmd_part = split_cmd_part(token, num_and_or);
	print_cmd_part(cmd_part);
	// while ()
	// {
	// }
}