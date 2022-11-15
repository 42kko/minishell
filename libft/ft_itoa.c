/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:49:00 by seokchoi          #+#    #+#             */
/*   Updated: 2022/04/05 13:43:59 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numlen(long num)
{
	size_t	len;

	len = 1;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num > 9)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	num;
	size_t	numlen;
	char	*str;

	num = (long)n;
	numlen = ft_numlen(num);
	str = (char *)malloc(sizeof(char) * (numlen + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	str[numlen] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[numlen - 1] = (num % 10) + '0';
		num /= 10;
		numlen--;
	}
	return (str);
}
