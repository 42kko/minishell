/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:00:01 by kko               #+#    #+#             */
/*   Updated: 2022/12/09 00:00:07 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_pipe(t_pipe *pip)
{
	pip->cnt = 0;
	pip->p = 0;
}

int	cnt_pipe(t_token **tok)
{
	int	ret;

	ret = 0;
	while ((*tok)->left)
	{
		if ((*tok)->type == TPIPE)
			ret++;
		*tok = (*tok)->left;
	}
	(*tok) = (*tok)->parent;
	return (ret);
}
