/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:34:40 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/02 18:59:06 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_cmd(t_token **token, char *line)
{
	char	**cmd;
	int		left;
	int		right;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (count_space_out_of_comma(line) + 1));
	if (!cmd)
		throw_error(MALLOC_ERR);
	right = 0;
	while (line[right])
	{
		left = right;
		cut_cmd(token, &cmd[i], &left, &right);
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
