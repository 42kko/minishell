/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:25:06 by seokhun           #+#    #+#             */
/*   Updated: 2022/04/04 19:36:27 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	front;
	size_t	back;

	if (!s1 || !set)
		return (0);
	front = 0;
	back = ft_strlen(s1);
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	while (s1[back - 1] && ft_strchr(set, s1[back - 1]) && back > front)
		back--;
	str = (char *)malloc(sizeof(char) * (back - front + 1));
	if (!str)
		return (NULL);
	else
		ft_strlcpy(str, &s1[front], back - front + 1);
	return (str);
}
