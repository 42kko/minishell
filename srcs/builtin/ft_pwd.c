/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:14:05 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 20:32:51 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **cmd)
{
	char	*pwd;
	char	*buf;

	(void) cmd;
	buf = ft_calloc(4096, 1);
	if (!buf)
		throw_error(MALLOC_ERR);
	pwd = getcwd(buf, 4096);
	printf("%s\n", pwd);
	free(buf);
}
