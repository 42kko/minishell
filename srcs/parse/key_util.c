/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:50:30 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/11 21:24:01 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_keycpy(char *dst, char *src, int dstsize)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

t_keys	*ft_keyslast(t_keys *keys)
{
	if (!keys)
		return (NULL);
	while (keys->next)
		keys = keys->next;
	return (keys);
}
