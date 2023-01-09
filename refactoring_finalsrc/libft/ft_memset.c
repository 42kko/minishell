/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:25:58 by seokchoi          #+#    #+#             */
/*   Updated: 2022/03/29 18:59:50 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	p;

	tmp = (unsigned char *)b;
	p = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		tmp[i] = p;
		i++;
	}
	return (b);
}
