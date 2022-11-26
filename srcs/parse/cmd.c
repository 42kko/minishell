/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:34:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/25 20:00:35 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_index_len_redirection(char *line, int *index)
{
	int			flag;
	t_oper_type	type;

	flag = 0;
	type = check_operator(line[*index]); // 어떤 리다이렉션인지 확인
	(*index)++;
	if (check_operator(line[*index]) == type) // 더블인지 체크
		(*index)++;
	else if (check_operator(line[*index]) != NO_TYPE) // 더블이 아니고 그 이외의 연산자가 오면 에러
		throw_error(SYNTAX_ERR);
	while (line[*index] == ' ') // space 스킵 
		(*index)++;
	push_index_until_space_or_oper(line, &(*index)); // 리다이렉션 파일이름의 끝까지 인덱스를 이동
}

char	**ft_split_cmd(char *line)
{
	char	**arr;
	int		left;
	int		right;
	int		i; 
	int		check_env;

	check_env = 0;
	i = 0;
	arr = malloc(sizeof(char *) * (count_space_out_of_comma(line) + 1));
	if (!arr)
		throw_error(MALLOC_ERR);
	right = 0;
	while (line[right])
	{
		left = right;
		if (line[right] == '<' || line[right] == '>')
		{
			push_index_len_redirection(line, &right);
			arr[i++] = ft_strdup_without_check_comma(line, left, right - left);
			while (line[right] == ' ')
				right++;
		}
		else
		{
			push_index_until_space_or_oper(line, &right); 
			if (line[right] == ' ' || line[right] == '\0' || ft_is_redir(line[right]) != NO_DIREC)
			{
				arr[i++] = ft_strdup_without_check_comma(line, left, right - left);
				while (line[right] == ' ')
					right++;
			}
			else if (line[right])
				right++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

void	set_cmd(t_token **token)
{
	(*token)->type = TCMD;
	(*token)->cmd = ft_split_cmd((*token)->line);
}
