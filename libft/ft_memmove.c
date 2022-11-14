/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:41:39 by seokchoi          #+#    #+#             */
/*   Updated: 2022/04/05 11:29:15 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = -1;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
	{
		while (++i < n)
			d[i] = s[i];
	}
	else
	{
		while (n)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
