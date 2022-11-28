/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:19:05 by seokhun           #+#    #+#             */
/*   Updated: 2022/03/29 18:41:34 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lit_len;

	i = 0;
	if (!(*little))
		return ((char *)big);
	lit_len = ft_strlen(little);
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && big[i + j] \
				&& little[j] && i + j < len)
				j++;
			if (j == lit_len)
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
