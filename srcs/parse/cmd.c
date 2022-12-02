/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:34:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/02 02:31:15 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	push_index_len_redirection(char *line, int *index)
{
	int			flag;
	t_oper_type	type;

	flag = 0;
	type = check_operator(line[*index]);
	(*index)++;
	if (check_operator(line[*index]) == type)
		(*index)++;
	else if (check_operator(line[*index]) != NO_TYPE)
		throw_error(SYNTAX_ERR);
	while (line[*index] == ' ')
		(*index)++;
	push_index_until_space_or_oper(line, &(*index));
}

int	check_is_start_cmd(char *line, int *right)
{
	if (line[(*right)] == ' ' || line[(*right)] == '\0' || \
	ft_is_redir(line[(*right)]) != NO_DIREC)
		return (1);
	return (0);
}

char	*ft_strdup_section(char *s, int left, int right)
{
	char	*str;
	int			i;

	i = 0;
	str = malloc(sizeof(char) * (right - left + 1));
	if (!str)
		throw_error(MALLOC_ERR);
	while(s[left] && left < right)
		str[i++] = s[left++];
	str[i] = '\0';
	return (str);
}
int	check_is_wave(t_token **token, char **arr, int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	push_index_until_space_or_oper(line, right);
	*arr= ft_strdup_section(line, *left, *right);
	// *arr = cpy_wout_com(token, line, (*left), (*right) - (*left)); // 요거 바꿔야함
	if (ft_strncmp(*arr, "~", 1) == 0)
	{
		free(*arr);
		*arr = ft_strdup(ft_getenv((*token)->info->env_list, "HOME"));
		if (!(*arr))
			throw_error(MALLOC_ERR);
		while (line[(*right)] == ' ')
				(*right)++;
		return (SECCESS);
	}
	free(*arr);
	*right = *left; 
	return (FAIL);
}

static int	cut_cmd(t_token **token, char **arr, int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	
	if (check_is_wave(token, arr, left, right))
		return (SECCESS);
	if (line[(*right)] == '<' || line[(*right)] == '>') // 리다이렉션이 올 경우,
	{
		push_index_len_redirection(line, right); // 리다리렉션의 길이를 구함
		*arr = cpy_wout_com(token, line, (*left), (*right) - (*left)); // 길이 만큼 자른다.
		while (line[(*right)] == ' ')
			(*right)++;
		return (SECCESS);
	}
	else
	{
		push_index_until_space_or_oper(line, &(*right));
		if (check_is_start_cmd(line, right))
		{
			*arr = cpy_wout_com(token, line, (*left), (*right) - (*left));
			while (line[(*right)] == ' ')
				(*right)++;
			return (SECCESS);
		}
		else if (line[(*right)])
			(*right)++;
	}
	return (FAIL);
}

char	**ft_split_cmd(t_token **token, char *line) // cmd를 적절히 쪼갠다
{
	char	**cmd;
	int		left;
	int		right;
	int		i;
	int		check_env;

	check_env = 0;
	i = 0;
	cmd = malloc(sizeof(char *) * (count_space_out_of_comma(line) + 1));
	if (!cmd)
		throw_error(MALLOC_ERR);
	right = 0;
	while (line[right])
	{
		left = right;
		if (cut_cmd(token, &cmd[i], &left, &right))
			i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	set_cmd(t_token **token)
{
	(*token)->type = TCMD;
	(*token)->cmd = ft_split_cmd(token, (*token)->line);
}
