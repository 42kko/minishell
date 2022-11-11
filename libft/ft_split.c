/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 23:22:39 by seokchoi          #+#    #+#             */
/*   Updated: 2022/04/05 13:43:18 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_arr(char *s, char c)
{
	size_t	cnt;
	char	**arr;

	cnt = 0;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			cnt++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	return (arr);
}

static char	*strdup_split(char const *s, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static void	*free_all(char **str, size_t l)
{
	size_t	i;

	i = 0;
	while (str[i] && i <= l)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static size_t	strlen_split(char const *s, char c)
{
	size_t		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		len;
	char		**arr;

	i = 0;
	len = 0;
	arr = ft_malloc_arr((char *)s, c);
	if (!arr)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = strlen_split(s, c);
			arr[i] = strdup_split(s, len);
			s += len;
			len = 0;
			if (!arr[i++])
				return (free_all(arr, i));
		}
		else
			s++;
	}
	arr[i] = 0;
	return (arr);
}
