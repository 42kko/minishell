/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 03:25:45 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 02:47:31 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	push_index_len_redirection(t_token **token, char *line, int *index)
{
	int			flag;
	t_oper_type	type;

	flag = 0;
	type = check_operator(line[*index]);
	(*index)++;
	if (check_operator(line[*index]) == type)
		(*index)++;
	if (check_operator(line[*index]) != NO_TYPE)
		throw_error_syntax(SYNTAX_ERR, *token);
	while (line[*index] == ' ')
		(*index)++;
	push_index_until_space_or_oper(line, &(*index));
}

static int	check_is_start_cmd(char *line, int *right)
{
	if (line[(*right)] && line[(*right)] != ' ' && \
	ft_is_redir(line[(*right)]) == NO_DIREC)
		return (1);
	return (0);
}

static void	set_redirection_cmd(t_token **token, char **arr, \
int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	push_index_len_redirection(token, line, right);
	*arr = cpy_wout_com(token, line, (*left), (*right) - (*left));
	while (line[(*right)] == ' ')
		(*right)++;
}

static int	set_normal_cmd(t_token **token, char **arr, int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	if (check_is_start_cmd(line, right))
	{
		push_index_until_space_or_oper(line, &(*right));
		*arr = cpy_wout_com(token, line, (*left), (*right) - (*left));
		while (line[(*right)] == ' ')
			(*right)++;
		return (SUCCESS);
	}
	else if (line[(*right)])
		(*right)++;
	return (FAIL);
}

void	cut_cmd(t_token **token, char **arr, int *left, int *right)
{
	char			*line;
	t_wave_type		check_wave;
	int				i;

	i = 0;
	line = (*token)->line;
	check_wave = check_is_wave(token, arr, left, right);
	if (check_wave == ONLY_WAVE)
		return ;
	if (line[(*right)] == '<' || line[(*right)] == '>')
		set_redirection_cmd(token, arr, left, right);
	else
		set_normal_cmd(token, arr, left, right);
	if (check_wave == MAYBE_HOME)
	{
		while ((*arr)[i] == '<' || (*arr)[i] == '>')
			i++;
		while ((*arr)[i] && (*arr)[i] == ' ')
			i++;
		if (ft_strncmp(*arr + i, "~/", 2) == 0)
			change_wave_to_home(token, arr, i);
	}
}
