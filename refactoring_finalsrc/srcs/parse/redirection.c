/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:59:30 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/03 16:35:33 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	attach_redir_token(t_token **token, \
t_token	**redir_token, char *file_name)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *redir_token;
	new = new_token((*token)->info);
	new->line = ft_strdup(file_name);
	check_type(&new);
	if (!new->line)
		throw_error(MALLOC_ERR);
	if (!(*redir_token))
	{
		(*redir_token) = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

static t_token	*pick_create_redir_tokens(t_token **token, char **cmd)
{
	int		i;
	t_token	*redir_token;

	i = 0;
	redir_token = NULL;
	while (cmd[i])
	{
		if (ft_is_redir(cmd[i][0]) != NO_DIREC)
			attach_redir_token(token, &redir_token, cmd[i]);
		i++;
	}
	return (redir_token);
}

static char	**pick_create_only_cmd_arr(char **arr, int only_cmd_len)
{
	char	**new_cmd_arr;
	int		i;
	int		k;

	if (only_cmd_len == 0)
		return (NULL);
	new_cmd_arr = malloc(sizeof(char *) * (only_cmd_len + 1));
	if (!new_cmd_arr)
		throw_error(MALLOC_ERR);
	new_cmd_arr[0] = NULL;
	k = 0;
	i = 0;
	while (arr[i])
	{
		if (ft_is_redir(arr[i][0]) == NO_DIREC)
		{
			new_cmd_arr[k] = ft_strdup(arr[i]);
			if (!new_cmd_arr[k])
				throw_error(MALLOC_ERR);
			k++;
		}
		i++;
	}
	new_cmd_arr[k] = NULL;
	return (new_cmd_arr);
}

static void	devide_redir_cmd(t_token **token, t_token **first)
{
	t_token	*redir_token;
	char	**new_cmd_arr;
	int		cmd_len;

	redir_token = pick_create_redir_tokens(token, (*token)->cmd);
	cmd_len = get_sec_arr_len((*token)->cmd) - token_list_len(redir_token);
	new_cmd_arr = pick_create_only_cmd_arr((*token)->cmd, cmd_len);
	if (cmd_len == 0)
		(*token)->type = TNOCMD;
	free_sec_arr((*token)->cmd);
	(*token)->cmd = new_cmd_arr;
	sort_token_order(token, first, redir_token);
}

void	set_type_remove_operator(t_token **token, t_token **first)
{
	if (first_check_operator((*token)->line[0]) != NO_TYPE)
		check_type(token);
	else if (have_brachek((*token)->line, *token) != 0)
	{
		(*token)->type = TBRACH;
		if ((*token)->line[0] != '(')
			throw_error_syntax(SYNTAX_ERR, *token);
		check_subshells(token, 0);
		if ((*token)->err_flag_syn != 1)
			get_redir_token(*token);
	}
	else if (*token)
	{
		set_cmd(token);
		devide_redir_cmd(token, first);
	}
}
