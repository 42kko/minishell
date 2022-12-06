/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:34:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/07 01:04:07 by seokchoi         ###   ########.fr       */
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
	if (check_operator(line[*index]) != NO_TYPE)
		throw_error(SYNTAX_ERR);
	while (line[*index] == ' ')
		(*index)++;
	push_index_until_space_or_oper(line, &(*index));
}

static int	check_is_start_cmd(char *line, int *right)
{
	if (line[(*right)] && line[(*right)] != ' ' && ft_is_redir(line[(*right)]) == NO_DIREC) // 
		return (1);
	return (0);
}

static void	set_redirection_cmd(t_token **token, char **arr, int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	push_index_len_redirection(line, right); // 리다리렉션의 길이를 구함 right를 변화시켜서 어디까지 리다이렉션인지 알려준다.
	*arr = cpy_wout_com(token, line, (*left), (*right) - (*left)); // 길이 만큼 자른다.
	while (line[(*right)] == ' ')
		(*right)++;
}

static int	set_normal_cmd(t_token **token, char **arr, int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	if (check_is_start_cmd(line, right)) // 의미있는 문자가 나온경우 즉 ' ' \0 <가 아닌경우
	{
		push_index_until_space_or_oper(line, &(*right)); // 어디까지 읽어야할지 right로 측정해준다. 
		*arr = cpy_wout_com(token, line, (*left), (*right) - (*left)); // 길이 만큼 자른다.
		while (line[(*right)] == ' ')
			(*right)++;
		return (SECCESS);
	}
	else if (line[(*right)])
		(*right)++;
	return (FAIL);
}

static void	cut_cmd(t_token **token, char **arr, int *left, int *right)
{
	char			*line;
	t_wave_type		check_wave;
	int				i;

	i = 0;
	line = (*token)->line; // 그럼 일단 line을 가져오고 left, right에는 어떤 정보가 있냐. line의 어디서부터 어디까지 끊을지가 적혀있다.
	check_wave = check_is_wave(token, arr, left, right); // wave의 여부를 판단
	if (check_wave == ONLY_WAVE) // ~ 밖에 없는 경우 바로 변경하고 리턴
		return ;
	if (line[(*right)] == '<' || line[(*right)] == '>') // 리다이렉션이 올 경우, <sfesdf
		set_redirection_cmd(token, arr, left, right);
	else // 1. "$HOME" 3.'seifj$osdjfe'"$LOGNAME"
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

char	**ft_split_cmd(t_token **token, char *line) // cmd를 적절히 쪼갠다
{
	char	**cmd;
	int		left;
	int		right;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (count_space_out_of_comma(line) + 1)); // 총 몇개로 컷이 되는지 확인 
	if (!cmd)
		throw_error(MALLOC_ERR);
	right = 0;
	while (line[right])
	{
		left = right;
		cut_cmd(token, &cmd[i], &left, &right); // cut_cmd에서 하나씩 자를 것이다. 1. "$HOME" 2. <sfesdf 3. 'seifj$osdjfe'"$LOGNAME"
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
