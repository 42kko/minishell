/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:34:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/06 21:36:12 by seokchoi         ###   ########.fr       */
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

static char	*ft_strdup_section(char *s, int left, int right)
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

static t_wave_type	check_is_wave(t_token **token, char **arr, int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	push_index_until_space_or_oper(line, right);
	*arr= ft_strdup_section(line, *left, *right);
	if (ft_strncmp(*arr, "~", 2) == 0) // ~ 혼자만 올 경우.
	{
		free(*arr);
		*arr = ft_strdup(ft_getenv((*token)->info->env_list, "~"));
		if (!(*arr))
			throw_error(MALLOC_ERR);
		while (line[(*right)] == ' ')
				(*right)++;
		return (ONLY_WAVE);
	}
	*right = *left;
	while (line[(*right)] == '<' || line[(*right)] == '>')
		(*right)++;
	while (line[(*right)] && line[(*right)] == ' ')
		(*right)++;
	if (ft_strncmp(line + *right, "~", 1) == 0)
	{
		free(*arr);
		*right = *left;
		return (MAYBE_HOME);
	}
	free(*arr);
	*right = *left;
	return (NO_WAVE);
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

static void	change_wave_to_home(t_token **token, char **arr, int i)
{
	char	*wave;
	char	*front_part;
	char	*back_part;
	char	*new;
	char	*tmp;

	wave = ft_getenv((*token)->info->env_list, "~");
	front_part = ft_substr(*arr, 0 , i);
	back_part = ft_strdup(*arr + i + 1);
	new = ft_strjoin(front_part, wave);
	if (!new)
		throw_error(MALLOC_ERR);
	tmp = new;
	new = ft_strjoin(new, back_part);
	if (!new)
		throw_error(MALLOC_ERR);
	free(tmp);
	free(wave);
	free(front_part);
	free(back_part);
	free(*arr);
	*arr = new;
}

static int	cut_cmd(t_token **token, char **arr, int *left, int *right)
{
	char			*line;
	t_wave_type		check_wave;
	int				i;

	i = 0;
	line = (*token)->line; // 그럼 일단 line을 가져오고 left, right에는 어떤 정보가 있냐. line의 어디서부터 어디까지 끊을지가 적혀있다.
	check_wave = check_is_wave(token, arr, left, right); // wave의 여부를 판단
	printf("check_wave = %d\n", check_wave);
	if (check_wave == ONLY_WAVE) // ~ 밖에 없는 경우 바로 변경하고 리턴
		return (SECCESS);
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
	return (SECCESS);
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
		// left = 어디서부터 cmd에 저장을 해야할지 알려준다.
		// right = 어디까지 읽을지 저장이 되어진다.
		if (cut_cmd(token, &cmd[i], &left, &right)) // cut_cmd에서 하나씩 자를 것이다. 1. "$HOME" 2. <sfesdf 3. 'seifj$osdjfe'"$LOGNAME"
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
