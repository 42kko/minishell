/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 01:06:10 by seokhun           #+#    #+#             */
/*   Updated: 2022/04/04 19:35:33 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (j < s1_len)
		str[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
