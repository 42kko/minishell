/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:41:25 by seokchoi          #+#    #+#             */
/*   Updated: 2022/07/08 15:57:03 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*rs;
	char		cc;
	size_t		i;

	i = 0;
	cc = (char)c;
	rs = NULL;
	while (s[i])
	{
		if (s[i] == cc)
			rs = &s[i];
		i++;
	}
	if (s[i] == cc)
		rs = &s[i];
	return ((char *)rs);
}
