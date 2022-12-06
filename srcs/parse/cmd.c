/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:34:40 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/07 03:26:03 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
