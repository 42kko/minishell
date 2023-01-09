/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:30:01 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/08 11:51:28 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static size_t	strlen_split(char const *s, char c)
{
	size_t		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static int	create_str_to_c(char const *s, char **arr, char c)
{
	size_t		len;

	len = strlen_split(s, c);
	*arr = strdup_split(s, len);
	if (!*arr)
		throw_error(MALLOC_ERR);
	return (len + 1);
}

int	is_dont_be_key(char *key)
{
	int		i;
	char	c;

	i = 0;
	if (ft_strlen(key) == 0)
		return (FAIL);
	if (key[0] >= '0' && key[0] <= '9')
		return (FAIL);
	while (key[i])
	{
		c = key[i];
		if ((c < '0' || c > '9') && (c < 'a' || c > 'z') && \
		(c < 'A' || c > 'Z') && c != '_')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	ft_split_for_env(char const *s, char **key, char **value)
{
	int	i;
	int	equal_flag;

	i = 0;
	equal_flag = 0;
	while (s[i])
	{
		if (s[i] == '=')
			equal_flag = 1;
		i++;
	}
	s += create_str_to_c(s, key, '=');
	if (equal_flag == 0)
		s--;
	create_str_to_c(s, value, 0);
	if (is_dont_be_key(*key) == FAIL)
		return (FAIL);
	if (equal_flag == 1)
		return (SUCCESS);
	else
		return (2);
}
