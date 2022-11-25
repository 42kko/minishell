/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:30:01 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/14 15:14:07 by seokchoi         ###   ########.fr       */
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

void	ft_split_for_env(char const *s, char **key, char **value)
{
	s += create_str_to_c(s, key, '=');
	create_str_to_c(s, value, 0);
}
