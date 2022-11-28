/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:36:06 by seokhun           #+#    #+#             */
/*   Updated: 2022/04/05 13:42:18 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*sub;

	i = 0;
	if (!s || start < 0)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
		return (ft_strdup(""));
	if (s_len - (size_t)start - 1 > len)
		sub = (char *)malloc(sizeof(char) * (len + 1));
	else
		sub = (char *)malloc(sizeof(char) * (s_len - start + 1));
	if (!sub)
		return (NULL);
	while (s[i] && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
