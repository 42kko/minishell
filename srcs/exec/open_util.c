/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:55:31 by kko               #+#    #+#             */
/*   Updated: 2022/12/08 23:56:08 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_redir(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp == ' ')
		tmp++;
	return (tmp);
}

void	close_util(int fd, t_token *tok)
{
	if (close(fd) < 0)
		err_msg("close err", tok, 0);
}
